#pragma once

#include "data.h"
HINSTANCE hInst;

#include "win_login.cpp"
#include "win_menu.cpp"
#include "win_medic.cpp"
#include "win_patient.cpp"

UserList user_list;

void GenerateData() {
    user_list.clear();
    user_list.saveToFile();
    user_list.addUser("danielmtz", "Daniel", "Martinez", "Barba", "danielmtz@clinic.com", "1234", DateToString(16, 05, 2025));
    user_list.saveToFile();
    user_list.loadFromFile();
    return;
}

void loadData() {
    user_list.loadFromFile();
    return;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    hInst = hInstance;

    // Load database
   // GenerateData();
    loadData();

    // Launch LogIn window
    DialogBox(hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);

    return 0;
}
