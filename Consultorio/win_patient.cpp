#include "data.h"

inline BOOL AddPatient(HWND hDlg) {
	// Array of IDC field IDs and corresponding variable pointers
	const int idcFields[] = {
		IDC_TXT_USR_AP_PATERNO,
		IDC_TXT_USR_AP_MATERNO,
		IDC_TXT_USR_NOMBRE,
		IDC_TXT_USR_PASS,
		IDC_TXT_USR_CEDULA
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(hDlg, idcFields[i]);
		if (IsEmpty(fieldValues[i])) {

			return FALSE;
		}
	}

        // Assign values to variables for clarity
        std::string lname1 = fieldValues[0];
        std::string lname2 = fieldValues[1];
        std::string fname = fieldValues[2];
        std::string password = fieldValues[3];
        std::string id = fieldValues[4];

        std::string email, date; // If needed, add their IDC fields to the array above

        user_list.addUser(id, fname, lname1, lname2, email, password, date);
        user_list.saveToFile();
        return TRUE;
    }


inline INT_PTR CALLBACK WindowProcPatient(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_MED_AGREGAR:
            bool success;
            success = AddPatient(hDlg);
            if (success) {
	            MessageBox(hDlg, L"Médico registrado!", L"Info", MB_OK);
            }
            else {

			MessageBox(hDlg, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
            }
            break;
            return TRUE;

        case IDC_BTN_MED_REGRESAR:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
