#include "data.h"
#include "controls.h"
#include "search.h"
#include "sort.h"

inline void GenerateMedicReport() {
	const int idcFields[] = {
		IDC_CBX_REPMED_ESPECIALIDAD,
		IDC_CBX_CIT_MEDICO,
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];
    HWND hListView = GetDlgItem(AppData::Instance().activeWindow, ID_LISTVIEW_REPORTE);

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	// Assign values to variables for clarity
	std::string spec = fieldValues[0];
	std::string medicid = fieldValues[1];
    std::string date_start = readDate(IDC_DTP_CIT_FECHA);
    std::string date_end = readDate(IDC_DTP_CIT_FECHA2);
   
    //SORT FIRST
    sortByDate();

    // THEN SEARCH
    std::vector<AppointmentNode*> foundApts = AppData::Instance().app_list.getAppointmentsByDatesMed(medicid, date_start, date_end);
    
    // Populate ListView
    for (size_t i = 0; i < foundApts.size(); ++i) {
        AppointmentNode* apt = foundApts[i];
        std::string medic_name = AppData::Instance().medic_list.getMedicNameById(apt->medicid);
        // Example columns: Cedula, Nombre (?), Fecha, Dia (?), Hora, Paciente, Estatus, Diagnóstico
        std::wstring rowData[] = {
            StringToWString(apt->medicid),
            StringToWString(medic_name),
            StringToWString(apt->date),
            StringToWString(getWeekDay(apt->date)), 
            StringToWString(apt->hour),
            StringToWString(apt->patientid),
            StringToWString(apt->status),
            StringToWString(apt->diagnosis)
        };

        FillListView(hListView, i, rowData);
    }

}

inline INT_PTR CALLBACK WindowProcReportMedic(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND hComboSpec, hComboMed;
    switch (message) {
    case WM_INITDIALOG:{
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();

        //ListView
	    const wchar_t* headers[] = { L"Cedula", L"Nombre", L"Fecha", L"Dia", L"Hora", L"Paciente", L"Estatus", L"Diagnostico" };
    	int widths[] = { 80, 120, 80, 80, 60, 120, 100, 140 };
        drawListView(ID_LISTVIEW_REPORTE, headers, widths);

        // ComboBox
        hComboSpec = GetDlgItem(hDlg, IDC_CBX_REPMED_ESPECIALIDAD);
        FillSpecialtyComboBox(hComboSpec);
        return TRUE;
    } break;

    case WM_COMMAND:

        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_CBX_REPMED_ESPECIALIDAD) {
            HWND hCombo = (HWND)lParam;
            int selIndex = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);

            if (selIndex != CB_ERR) {
                wchar_t buffer[256];
                SendMessage(hCombo, CB_GETLBTEXT, selIndex, (LPARAM)buffer);
                std::vector<std::string> foundMeds = AppData::Instance().medic_list.getMedicIdsBySpec(wcharToChar(buffer));
                hComboMed = GetDlgItem(hDlg, IDC_CBX_CIT_MEDICO);
				for (const auto& id : foundMeds) {
					std::wstring wname = StringToWString(id); // Use the utility!
                    SendMessage(hComboMed, CB_RESETCONTENT, 0, 0);
					SendMessage(hComboMed, CB_ADDSTRING, 0, (LPARAM)wname.c_str());
				}
            }
            return TRUE;
        }

        switch (LOWORD(wParam)) {

        case IDC_BTN_REPMED_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;

        case IDC_BTN_REPMED_BUSCAR:
            GenerateMedicReport();
            return TRUE;

        case IDC_BTN_REPMED_LIMPIAR:
            CleanReportFields(true);
            return TRUE;
        }

        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
