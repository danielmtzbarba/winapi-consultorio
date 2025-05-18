#pragma once

#include "resources.h"

#include "specs.h"
#include "users.h"
#include "medics.h"
#include "patients.h"

extern INT_PTR CALLBACK WindowProcLogin(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSignUp(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMenu(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMedic(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcPatient(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSpec(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcRooms(HWND, UINT, WPARAM, LPARAM);

// Global AppData singleton
class AppData {
public:

    HINSTANCE hInst;
    HWND activeWindow;

    std::string userId;

	std::ofstream log;

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

        // Only create samples if the list is empty
        if (!patient_list.head) {
            patient_list.createSamplePatients();
        }
        if (!medic_list.head) {
            medic_list.createSampleMedics();
        }
        if (!spec_list.head) {
            spec_list.createSampleSpecialties();
        }
    }

    void writeDebugLog() {
        if (log.is_open()) {
		    medic_list.printList();
            log << " ------- " << std::endl;
        }
    }

    void logMessage(const std::string& message) {
        if (log.is_open()) {
            log << message << std::endl;
        }
    }

    // Prevent copy/move
    AppData(const AppData&) = delete;
    AppData& operator=(const AppData&) = delete;

private:
    AppData() {
        log.open("log.txt", std::ios::app);
        loadDatabase();
    }
};

inline void FillSpecialtyComboBox(HWND hCombo) {
    SendMessage(hCombo, CB_RESETCONTENT, 0, 0);

    SpecNode* current = AppData::Instance().spec_list.head;
    while (current) {
        std::wstring wname = StringToWString(current->name); // Use the utility!
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)wname.c_str());
        current = current->next;
    }
}

inline void FillSpecialtyListBox(HWND hList) {
    SendMessage(hList, LB_RESETCONTENT, 0, 0);

    SpecNode* current = AppData::Instance().spec_list.head;
    while (current) {
        std::wstring wname = StringToWString(current->name); // Use the utility!
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)wname.c_str());
        current = current->next;
    }
}

// Helper to set a text field
inline void SetTextBox(int id, const std::string& value) {
    std::wstring wvalue = StringToWString(value);
    SetWindowTextW(GetDlgItem(AppData::Instance().activeWindow, id), wvalue.c_str());
}


// Helper to select a value in a combobox by string
inline void SetComboBoxByString(int id, const std::string& value) {
    HWND hCombo = GetDlgItem(AppData::Instance().activeWindow, id);
    std::wstring wvalue = StringToWString(value);
    SendMessage(hCombo, CB_SELECTSTRING, -1, (LPARAM)wvalue.c_str());
}
