#include "data.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AppData::Instance().hInst = hInstance;

    // Now launch the dialog
    DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_INICIO_SESION), NULL, WindowProcLogin);

    return 0;
}
