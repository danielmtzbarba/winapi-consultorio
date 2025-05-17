#pragma once

#include "resources.h"
#include "users.h"
#include "medics.h"
#include "patients.h"
#include "specs.h"

extern INT_PTR CALLBACK WindowProcLogin(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSignUp(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMenu(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMedic(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcPatient(HWND, UINT, WPARAM, LPARAM);

// Global AppData singleton
class AppData {
public:

    HINSTANCE hInst;

    std::string userId;

	UserList user_list;
	MedicList medic_list;
    PatientList patient_list;
    SpecList spec_list;

    static AppData& Instance() {
        static AppData instance;
        return instance;
    }

    // Loads all app data (users, medics, etc.)
    void loadDatabase() {
        user_list.loadFromFile();
        medic_list.loadFromFile();
        patient_list.loadFromFile();
        spec_list.loadFromFile();
    }

    // Prevent copy/move
    AppData(const AppData&) = delete;
    AppData& operator=(const AppData&) = delete;

private:
    AppData() {
        loadDatabase();
    }
};

