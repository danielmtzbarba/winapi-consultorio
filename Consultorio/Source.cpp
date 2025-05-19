#pragma once

#include "data.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AppData::Instance().hInst = hInstance;

    // Ensure the database is loaded before showing any dialogs
    AppData::Instance().loadDatabase();

    // Now launch the dialog
    DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);

    return 0;
}
