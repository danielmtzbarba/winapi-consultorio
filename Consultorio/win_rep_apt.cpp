#include "data.h"
#include "controls.h"

inline void GenerateAptReport() {
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
    
    std::vector<AppointmentNode*> foundApts = AppData::Instance().app_list.getAppointmentsByDates(medicid, date_start, date_end);
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

inline INT_PTR CALLBACK WindowProcReportApt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND hComboPat;
    switch (message) {
    case WM_INITDIALOG:{
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();

        //ListView
	    const wchar_t* headers[] = { L"Cedula", L"Nombre", L"Fecha", L"Dia", L"Hora", L"Paciente", L"Estatus", L"Diagnostico" };
    	int widths[] = { 80, 120, 80, 80, 60, 120, 100, 140 };
        drawListView(ID_LISTVIEW_REPORTE, headers, widths);

        // ComboBox
        hComboPat = GetDlgItem(hDlg, IDC_CBX_CIT_MEDICO);
        FillSpecialtyComboBox(hComboPat);

        return TRUE;
    } break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case IDC_BTN_REPMED_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;

        case IDC_BTN_REPMED_BUSCAR:
            GenerateAptReport();
            return TRUE;

        case IDC_BTN_REPMED_LIMPIAR:
            CleanReportFields();
            return TRUE;
        }

        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
