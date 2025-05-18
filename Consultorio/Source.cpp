#pragma once

#include "data.h"

#include "win_login.cpp"
#include "win_menu.cpp"
#include "win_medic.cpp"
#include "win_patient.cpp"

void GenerateData() {
    AppData::Instance().user_list.clear();
    AppData::Instance().user_list.saveToFile();
    AppData::Instance().user_list.addUser("danielmtz", "Daniel", "Martinez", "Barba", "danielmtz@clinic.com", "1234", DateToString(16, 05, 2025));
    AppData::Instance().user_list.saveToFile();
    AppData::Instance().user_list.loadFromFile();
    return;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AppData::Instance().hInst = hInstance;

    // Ensure the database is loaded before showing any dialogs
    AppData::Instance().loadDatabase();

    // Now launch the dialog
    DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);

    return 0;
}
