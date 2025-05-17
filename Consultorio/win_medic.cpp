#include "data.h"

inline BOOL AddMedic(HWND hDlg) {
	// Array of IDC field IDs and corresponding variable pointers

	const int idcFields[] = {
		IDC_TXT_MED_CEDULA,
		IDC_TXT_MED_NOMBRE,
		IDC_TXT_MED_AP_PATERNO,
		IDC_TXT_MED_AP_MATERNO,
		IDC_TXT_MED_CORREO,
		IDC_TXT_MED_TELEFONO,
		IDC_CBX_MED_ESPECIAL,
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
        std::string id = fieldValues[0];
        std::string lname1 = fieldValues[1];
        std::string lname2 = fieldValues[2];
        std::string fname = fieldValues[3];
        std::string email = fieldValues[4];
        std::string phone = fieldValues[5];
        std::string spec = fieldValues[6];

        AppData::Instance().medic_list.addMedic(id, fname, lname1, lname2, email, phone, spec, AppData::Instance().userId);
        return TRUE;
    }


inline INT_PTR CALLBACK WindowProcMedic(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_MED_AGREGAR:
            bool success;
            success = AddMedic(hDlg);
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
