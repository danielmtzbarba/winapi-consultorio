#include "data.h"

inline INT_PTR CALLBACK WindowProcMenu(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow(hDlg);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDC_BTN_MENU_LOGOUT:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_INICIO_SESION), NULL, WindowProcLogin);
            return TRUE;

        case IDC_BTN_MENU_MEDICOS:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_GESTION_MEDICOS), NULL, WindowProcMedic);
            return TRUE;

        case IDC_BTN_MENU_PACIENTES:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_DATOS_PACIENTE), NULL, WindowProcPatient);
            return TRUE;

        case IDC_BTN_MENU_ESPECIALIDAD:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_GESTION_ESPECIALIDADES), NULL, WindowProcSpec);
            return TRUE;

        case IDC_BTN_MENU_CONSULTORIOS:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_CONSULTORIOS), NULL, WindowProcRooms);
            return TRUE;
        }

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
