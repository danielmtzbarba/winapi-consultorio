#include "data.h"
#include "controls.h"

inline void ClearPatientFields() {
    SetTextBox(IDC_TXT_PAC_ID, "");
    SetTextBox(IDC_TXT_PAC_NOMBRE, "");
    SetTextBox(IDC_TXT_PAC_AP_PATERNO, "");
    SetTextBox(IDC_TXT_PAC_AP_MATERNO, "");
    SetTextBox(IDC_TXT_PAC_CORREO, "");
    SetTextBox(IDC_TXT_PAC_TELEFONO, "");
    SetTextBox(IDC_TXT_PAC_EDAD, "");
    HWND hCombo = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_PAC_GENERO);
    if (hCombo) {
        SendMessage(hCombo, CB_SETCURSEL, -1, 0); // Deselect any selection
    }
}

inline void searchPatient() {
    std::string id;
    id =  ReadTextBox(IDC_TXT_PAC_ID);
    PatientNode* found = AppData::Instance().patient_list.searchPatient(id);
    if (!found) {
        ClearPatientFields();
		MessageBox(AppData::Instance().activeWindow, L"ID no registrado!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }
    SetTextBox(IDC_TXT_PAC_ID, found->id);
    SetTextBox(IDC_TXT_PAC_NOMBRE, found->fname);
    SetTextBox(IDC_TXT_PAC_AP_PATERNO, found->lname1);
    SetTextBox(IDC_TXT_PAC_AP_MATERNO, found->lname2);
    SetTextBox(IDC_TXT_PAC_CORREO, found->email);
    SetTextBox(IDC_TXT_PAC_TELEFONO, found->phone);
    SetTextBox(IDC_TXT_PAC_EDAD, found->age);
    SetComboBoxByString(IDC_CBX_PAC_GENERO, found->gender);

}

inline BOOL AddPatient(bool update) {
	// Array of IDC field IDs and corresponding variable pointers
	const int idcFields[] = {
		IDC_TXT_PAC_ID,
		IDC_TXT_PAC_NOMBRE,
		IDC_TXT_PAC_AP_PATERNO,
		IDC_TXT_PAC_AP_MATERNO,
		IDC_TXT_PAC_CORREO,
		IDC_TXT_PAC_TELEFONO,
		IDC_CBX_PAC_GENERO,
		IDC_TXT_PAC_EDAD,
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {

			return FALSE;
		}
	}

        // Assign values to variables for clarity
        std::string id = fieldValues[0];
        std::string fname = fieldValues[1];
        std::string lname1 = fieldValues[2];
        std::string lname2 = fieldValues[3];

        std::string email = fieldValues[4];
        std::string phone = fieldValues[5];
        std::string gender = fieldValues[6];
        std::string age = fieldValues[7];

        if (update) {
            AppData::Instance().patient_list.updatePatientById(id, fname, lname1, lname2, email, phone, gender, age, AppData::Instance().userId);
        }
        else {
            AppData::Instance().patient_list.addPatient(id, fname, lname1, lname2, email, phone, gender, age, AppData::Instance().userId);
        }

        return TRUE;
 }

inline void removePatient() {
    std::string id;
    id = ReadTextBox(IDC_TXT_PAC_ID);
    bool isDeleted = AppData::Instance().patient_list.removePatientById(id);
    ClearPatientFields();
    if (isDeleted) {
	    MessageBox(AppData::Instance().activeWindow, L"Registro eliminado!", L"Info", MB_OK);
    }
}

inline INT_PTR CALLBACK WindowProcPatient(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    HWND hCombo;
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
        // Get the combo box control by its ID
        hCombo = GetDlgItem(hDlg, IDC_CBX_PAC_GENERO);
        // Add a string to the combo box
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"F");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"M");
        return TRUE;

    case WM_COMMAND:
        bool success;
        switch (LOWORD(wParam)) {
        case IDC_BTN_PAC_AGREGAR:
            success = AddPatient(false);
            if (success) {
	            MessageBox(hDlg, L"Paciente registrado!", L"Info", MB_OK);
            }
            else {

			MessageBox(hDlg, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
            }
            break;
            return TRUE;

        case IDC_BTN_PAC_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;

        case IDC_BTN_PAC_MODIFICAR:
            success = AddPatient(true);
            if (success) {
	            MessageBox(hDlg, L"Registro modificado!", L"Info", MB_OK);
            }
            return TRUE;

        case IDC_BTN_PAC_CONSULTAR:
            searchPatient();
            return TRUE;

        case IDC_BTN_PAC_ELIMINAR:
            removePatient();
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }

    return FALSE;
}
