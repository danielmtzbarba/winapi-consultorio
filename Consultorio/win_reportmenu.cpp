#include "data.h"
#include "controls.h"

inline INT_PTR CALLBACK WindowProcReportMenu(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDC_BTN_MED_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;

        case IDC_BTN_RPT_MEDICOS:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_REPORTE_MEDICOS), NULL, WindowProcReportMedic);
            return TRUE;

        case IDC_BTN_RPT_CITAS:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_REPORTE_CITAS), NULL, WindowProcReportApt);
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
