#include "data.h"

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
