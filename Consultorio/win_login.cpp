#include "utils.h"
#include "data.h"
#include "resource.h"

inline INT_PTR CALLBACK WindowProcLogin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    std::string id, password;
    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
