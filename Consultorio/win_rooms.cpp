#include "data.h"
#include "controls.h"
#include "search.h"

inline void searchID() {
    std::string id;

    id =  ReadTextBox(IDC_TXT_CON_CEDULA);

    // BINARY SEARCH
    MedicNode* found =  searchMedicById(id);

    HWND hList = GetDlgItem(AppData::Instance().activeWindow, IDC_LST_CONSULTORIOSGRANDE);

    if (!found) {
        SetTextBox(IDC_TXT_CON_ESP, "");
        SendMessage(hList, LB_RESETCONTENT, 0, 0);
		MessageBox(AppData::Instance().activeWindow, L"Cedula no registrada!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    SetTextBox(IDC_TXT_CON_ESP, found->spec);
    FillRoomsListBox(hList, found->spec);

}
inline std::string readRoomDate() {
    SYSTEMTIME st = { 0 };
    HWND hDatePicker = GetDlgItem(AppData::Instance().activeWindow, IDC_DATETIMEPICKER2);
    std::string date_str;
    if (SendMessage(hDatePicker, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
        // Now `st` contains the selected date/time.
        // Example: convert to string
        wchar_t buffer[100];
        swprintf(buffer, 100, L"%02d-%02d-%04d", st.wDay, st.wMonth, st.wYear);
        date_str = wstringToString(buffer);
    }
    else {
        MessageBox(AppData::Instance().activeWindow, L"DTM_GETSYSTEMTIME failed or no date selected.", L"Error", MB_OK | MB_ICONERROR);
    }

    return date_str;
}


inline void addAppointmentSlots() {
	// Array of IDC field IDs and corresponding variable pointers
	const int idcFields[] = {
		IDC_TXT_CON_CEDULA,
		IDC_TXT_CON_ESP,
		IDC_TXT_HORA_INICIO_LUN,
		IDC_TXT_HORA_FIN_LUN,
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];
    std::string selectedRoom;

    HWND hList = GetDlgItem(AppData::Instance().activeWindow, IDC_LST_CONSULTORIOSGRANDE);
    int index = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);

    if (index != LB_ERR) {
        wchar_t buffer[256];
        SendMessage(hList, LB_GETTEXT, index, (LPARAM)buffer);
        selectedRoom = wcharToChar(buffer);
    }
    else {
        // ******* VERIFICACION ADICIONAL: Asegurarse de que se seleccione consultorio
		MessageBox(AppData::Instance().activeWindow, L"Seleccione consultorio!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
		    MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	// Assign values to variables for clarity
	std::string medicid = fieldValues[0];
	std::string spec = fieldValues[1];
	std::string hour1_str = fieldValues[2];
	std::string hour2_str = fieldValues[3];

	std::string date = readRoomDate();
    if (!dateValidation(date)) {
        MessageBoxA(AppData::Instance().activeWindow, "Fecha Invalida", "Info", MB_OK | MB_ICONWARNING);
        return;
    }

    std::string id, hourid;
	int hour1, hour2;
	hour2 = StringToInt(hour2_str);
    bool success = FALSE;
	for (hour1 = StringToInt(hour1_str); hour1 <= hour2; hour1++) {
		hourid= std::to_string(hour1) + "-" + std::to_string(hour1 + 1);
		id = selectedRoom + "-" + date + "-" + hourid;
	    success = AppData::Instance().app_list.addAppointment(id, date, hourid,
		    spec, selectedRoom, medicid, "", "DISPONIBLE", "", AppData::Instance().userId);
        if (!success) {
            std::string msg = "Consultorio " + selectedRoom + " ocupado de " + hourid + " en " + date;
            MessageBoxA(AppData::Instance().activeWindow, msg.c_str(), "Info", MB_OK | MB_ICONWARNING);
            return;
        }
	}
    if (success) {
	    MessageBox(AppData::Instance().activeWindow, L"Consultorio reservado!", L"Info", MB_OK | MB_ICONINFORMATION);
    }
	return;
}

inline INT_PTR CALLBACK WindowProcRooms(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
        return TRUE;

    case WM_COMMAND:
        bool success;
        switch (LOWORD(wParam)) {

        case IDC_BTN_CON_BUSCAR:
            searchID();
            return TRUE;

        case IDC_BTN_GUARDAR:
            addAppointmentSlots();
            return TRUE;

        case IDC_BTN_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }

    return FALSE;
}
