#include "data.h"
#include "controls.h"
#include "search.h"
#include "sort.h"

inline void GenerateAptReport() {
    HWND hListView = GetDlgItem(AppData::Instance().activeWindow, ID_LISTVIEW_REPORTE);
		
        std::string patientid = ReadTextBox(IDC_CBX_CIT_MEDICO);
		if (IsEmpty(patientid)) {
			MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
    std::string date_start = readDate(IDC_DTP_CIT_FECHA);
    std::string date_end = readDate(IDC_DTP_CIT_FECHA2);
    
    //SORT FIRST
    sortByDate();

    // BINARY SEARCH FOR PATIENTID
    auto patientApts = binarySearchNodes<AppointmentNode, std::string>(
        AppData::Instance().app_list.toVector(),
        patientid,
        std::equal_to<>(),    
        [](AppointmentNode* node) { return node->patientid; }
    );

    // SORT BEFORE SECOND SEARCH
    std::sort(patientApts.begin(), patientApts.end(), [](AppointmentNode* a, AppointmentNode* b) {
        return dateStrToIntTuple(a->date) < dateStrToIntTuple(b->date);
        });

    // BINARY SEARCH FOR DATSE
    auto foundApts = rangeSearchNodes<AppointmentNode, std::tuple<int, int, int>>(
        patientApts,
        dateStrToIntTuple(date_start),
        dateStrToIntTuple(date_end),
        [](AppointmentNode* node) { return dateStrToIntTuple(node->date); }
    );

    // POPULATE LISTVIEW
    for (size_t i = 0; i < foundApts.size(); ++i) {
        AppointmentNode* apt = foundApts[i];
        std::string medic_name = AppData::Instance().medic_list.getMedicNameById(apt->medicid);
        std::string patient_name = AppData::Instance().patient_list.getPatientNameById(apt->patientid);
        // Example columns: Cedula, Nombre (?), Fecha, Dia (?), Hora, Paciente, Estatus, Diagnóstico
        std::wstring rowData[] = {
            StringToWString(apt->patientid),
            StringToWString(patient_name),
            StringToWString(apt->date),
            StringToWString(getWeekDay(apt->date)), 
            StringToWString(apt->hour),
            StringToWString(medic_name),
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
        const wchar_t* headers[] = { L"ID Paciente", L"Nombre", L"Fecha", L"Dia", L"Hora", L"Medico", L"Especialidad", L"Estatus", L"Diagnostico" };
        int widths[] = { 80, 120, 80, 80, 60, 120, 100, 100, 140 };

        drawListView(ID_LISTVIEW_REPORTE, headers, widths);

        // ComboBox
        hComboPat = GetDlgItem(hDlg, IDC_CBX_CIT_MEDICO);
        FillPatientComboBox(hComboPat);

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
            CleanReportFields(false);
            return TRUE;
        }

        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
