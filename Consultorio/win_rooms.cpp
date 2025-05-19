#include "data.h"

inline void searchID() {
    std::string id;

    id =  ReadTextBox(AppData::Instance().activeWindow, IDC_TXT_CON_CEDULA);
    MedicNode* found = AppData::Instance().medic_list.searchMedic(id);
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
inline std::string readDate() {
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

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(AppData::Instance().activeWindow, idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			return;
		}
	}
	// Assign values to variables for clarity
	std::string medicid = fieldValues[0];
	std::string spec = fieldValues[1];
	std::string hour1_str = fieldValues[2];
	std::string hour2_str = fieldValues[3];

	std::string date = readDate();
    std::string id;
	int hour1, hour2;
	hour2 = StringToInt(hour2_str);
	for (hour1 = StringToInt(hour1_str); hour1 <= hour2; hour1++) {
		id = selectedRoom + "-" + date + "-" + std::to_string(hour1);
	    AppData::Instance().app_list.addAppointment(id, date, std::to_string(hour1),
		    spec, selectedRoom, medicid, "", "DISPONIBLE", "", AppData::Instance().userId);
	}
    MessageBox(AppData::Instance().activeWindow, L"Registro actualizado!", L"Info", MB_OK | MB_ICONINFORMATION);
    AppData::Instance().writeDebugLog();
	return;
}

inline INT_PTR CALLBACK WindowProcRooms(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    HWND hCombo;
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow(hDlg);
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
