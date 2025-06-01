#include "data.h"
#include "controls.h"

inline std::string readAppDate() {
    SYSTEMTIME st = { 0 };
    HWND hDatePicker = GetDlgItem(AppData::Instance().activeWindow, IDC_DTP_CIT_FECHA);
    std::string date_str;
    if (SendMessage(hDatePicker, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
        // `st` contiene la fecha/hora
        // Ejemplo: lo convierte a string
        wchar_t buffer[100];
        swprintf(buffer, 100, L"%02d-%02d-%04d", st.wDay, st.wMonth, st.wYear);
        date_str = wstringToString(buffer);
    }
    return date_str;
}

inline void checkAvailability() {
	const int idcFields[] = {
		IDC_CBX_CIT_ESPECIALIDAD,
		IDC_CBX_CIT_MEDICO,
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// lee y checa cada archivo
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	// Se asigna un valor a la variable
	std::string spec = fieldValues[0];
	std::string medicid = fieldValues[1];
    std::string date = readAppDate();
   
    if (!dateValidation(date)) {
        MessageBoxA(AppData::Instance().activeWindow, "Fecha Invalida", "Info", MB_OK | MB_ICONWARNING);
        return;
    }

	std::vector<std::string> foundHours = AppData::Instance().app_list.getAppointmentsByMedic(medicid, date);
	HWND hComboHours = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_CIT_HORA);

    // Limpia las listbox de las horas
    SendMessage(hComboHours, CB_RESETCONTENT, 0, 0);

    if (foundHours.empty()) {
        MessageBox(AppData::Instance().activeWindow, L"No hay disponibilidad para el médico seleccionado.", L"Sin disponibilidad", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(AppData::Instance().activeWindow, L"Las horas disponibles han sido actualizadas.", L"Disponibilidad actualizada", MB_OK | MB_ICONINFORMATION);

        for (const std::string& hourStr : foundHours) {//convierte el string a un numero entero
            try {
                int startHour = std::stoi(hourStr);
                std::string range = std::to_string(startHour) + "-" + std::to_string(startHour + 1);//Aumenta una hora y lo hace un rango "5-6"

                // Lo convierte en widestring antes de meterlo al ComboBox
                std::wstring wideRange(range.begin(), range.end());//convierte el string a un Wstring
                SendMessage(hComboHours, CB_ADDSTRING, 0, (LPARAM)wideRange.c_str());//envia el texto a la combobox como un menu desplegable
            }
            catch (...) {
                
            }
        }
    }
    // Selecciona el primer objeto
    SendMessage(hComboHours, CB_SETCURSEL, 0, 0);
}

inline void checkAppointment() {
	const int idcFields[] = {
		IDC_CBX_CIT_ESPECIALIDAD,
		IDC_CBX_CIT_MEDICO,
        IDC_CBX_CIT_HORA,
        IDC_TXT_PAC_ID
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// Lee y verifica el archivo
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	// Asignamos valores a las variables
	std::string spec = fieldValues[0];
	std::string medicid = fieldValues[1];
	std::string hour = fieldValues[2];
	std::string patientid = fieldValues[3];
    std::string date = readAppDate();

    PatientNode* found = AppData::Instance().patient_list.searchPatient(patientid);
    if (!found) {
		MessageBox(AppData::Instance().activeWindow, L"ID de Paciente no registrado!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }
    AppointmentNode* nodeptr = AppData::Instance().app_list.getAppointmentPtr(medicid, date, hour);
    if (nodeptr) {
        nodeptr->patientid = patientid;
        nodeptr->status = "RESERVADA";
        AppData::Instance().app_list.saveToFile();
        MessageBox(AppData::Instance().activeWindow, L"Cita Agendada.", L"Citas", MB_OK | MB_ICONINFORMATION);
    }
    else {
		MessageBox(AppData::Instance().activeWindow, L"Error al agendar cita!", L"Error", MB_OK | MB_ICONERROR);
    }
}

inline void searchPatientAppointments() {
    std::string patientid = ReadTextBox(IDC_TXT_PAC_ID2);
	if (IsEmpty(patientid)) {
		MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	std::vector<std::string> foundAppointments = AppData::Instance().app_list.getAppointmentsByPatient(patientid);
    
    HWND hComboApp = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_CIT_PACIENTE3);
    SendMessage(hComboApp, CB_RESETCONTENT, 0, 0);
	for (const std::string& app : foundAppointments) {
			// lo convierte a un wString antes de agregar valores
			std::wstring wideRange(app.begin(), app.end());
			SendMessage(hComboApp, CB_ADDSTRING, 0, (LPARAM)wideRange.c_str());
		}
}


inline void updateAppointment() {
	const int idcFields[] = {
		IDC_TXT_PAC_ID2,
		IDC_CBX_CIT_PACIENTE3,
        IDC_CBX_CIT_ESTATUS,
        IDC_TXT_CIT_DIAGNOSTICO
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// Lee y checa cada arhivo
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			MessageBox(AppData::Instance().activeWindow, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	// Asigna valores 
	std::string patientid = fieldValues[0];
	std::string aptid = fieldValues[1];
	std::string status = fieldValues[2];
	std::string diag = fieldValues[3];

    PatientNode* found = AppData::Instance().patient_list.searchPatient(patientid);
    if (!found) {
		MessageBox(AppData::Instance().activeWindow, L"ID de Paciente no registrado!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }
    AppointmentNode* nodeptr = AppData::Instance().app_list.getAppointmentById(aptid);
    if (nodeptr) {
        nodeptr->patientid = patientid;
        nodeptr->status = status;
        nodeptr->diagnosis = diag;
        AppData::Instance().app_list.saveToFile();
        MessageBox(AppData::Instance().activeWindow, L"Cita Actualizada.", L"Citas", MB_OK | MB_ICONINFORMATION);
    }
    else {
		MessageBox(AppData::Instance().activeWindow, L"Error al actualizar cita!", L"Error", MB_OK | MB_ICONERROR);
    }
}

inline INT_PTR CALLBACK WindowProcCitas(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    HWND hComboSpec, hComboMed, hComboApp;
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
		hComboSpec = GetDlgItem(hDlg, IDC_CBX_CIT_ESPECIALIDAD);
        FillSpecialtyComboBox(hComboSpec);
        hComboApp = GetDlgItem(hDlg, IDC_CBX_CIT_ESTATUS);
	    SendMessage(hComboApp, CB_ADDSTRING, 0, (LPARAM)L"DISPONIBLE");
	    SendMessage(hComboApp, CB_ADDSTRING, 0, (LPARAM)L"RESERVADA");
	    SendMessage(hComboApp, CB_ADDSTRING, 0, (LPARAM)L"CANCELADA");
	    SendMessage(hComboApp, CB_ADDSTRING, 0, (LPARAM)L"COMPLETADA");
        return TRUE;

    case WM_COMMAND:

        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_CBX_CIT_ESPECIALIDAD) {
            HWND hCombo = (HWND)lParam;
            int selIndex = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);

            if (selIndex != CB_ERR) {
                wchar_t buffer[256];
                SendMessage(hCombo, CB_GETLBTEXT, selIndex, (LPARAM)buffer);
                std::vector<std::string> foundMeds = AppData::Instance().medic_list.getMedicIdsBySpec(wcharToChar(buffer));
                hComboMed = GetDlgItem(hDlg, IDC_CBX_CIT_MEDICO);
                SendMessage(hComboMed, CB_RESETCONTENT, 0, 0);
				for (const auto& id : foundMeds) {
					std::wstring wname = StringToWString(id); 
					SendMessage(hComboMed, CB_ADDSTRING, 0, (LPARAM)wname.c_str());
				}
            }
            return TRUE;
        }

        switch (LOWORD(wParam)) {

        case IDC_BTN_CIT_BUSCAR:
            checkAvailability();
            return TRUE;

        case IDC_BTN_CIT_RESERVAR:
            checkAppointment();
            return TRUE;

        case IDC_BTN_CIT_RESERVAR2:
            searchPatientAppointments();
            return TRUE;

        case IDC_BTN_CIT_REG_DIAGNOSTICO:
            updateAppointment();
            return TRUE;

        case IDC_BTN_CIT_REGRESAR:
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
