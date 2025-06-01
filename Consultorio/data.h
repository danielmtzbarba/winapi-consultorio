#pragma once

#include "resources.h"

#include "specs.h"
#include "users.h"
#include "medics.h"
#include "patients.h"
#include "rooms.h"
#include "appointments.h"

extern INT_PTR CALLBACK WindowProcLogin(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSignUp(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMenu(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMedic(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcPatient(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSpec(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcRooms(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcCitas(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcReportMenu(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcReportMedic(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcReportApt(HWND, UINT, WPARAM, LPARAM);

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
    RoomList room_list;
    AppointmentList app_list;

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
        room_list.loadFromFile();
        app_list.loadFromFile();
    }

    void writeDebugLog() {
        if (log.is_open()) {
            logMessage("--- Start Debug Log");
            AppointmentNode* node = app_list.head;
            while (node) {
                log << node->date << std::endl;
                node = node->next;
            }
            logMessage("--- End Debug Log");
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
        medic_list.createSampleMedics();
        patient_list.createSamplePatients();
        //writeDebugLog();
    }
};

