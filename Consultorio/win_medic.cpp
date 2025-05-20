#include "data.h"
#include "controls.h"
#include "search.h"

inline void ClearMedicFields() {
    SetTextBox(IDC_TXT_MED_CEDULA, "");
    SetTextBox(IDC_TXT_MED_NOMBRE, "");
    SetTextBox(IDC_TXT_MED_AP_PATERNO, "");
    SetTextBox(IDC_TXT_MED_AP_MATERNO, "");
    SetTextBox(IDC_TXT_MED_CORREO, "");
    SetTextBox(IDC_TXT_MED_TELEFONO, "");
    HWND hCombo = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_MED_ESPECIAL);
    if (hCombo) {
        SendMessage(hCombo, CB_SETCURSEL, -1, 0); // Deselect any selection
    }
}

inline BOOL AddMedic(bool update) {
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
        std::string spec = fieldValues[6];
        
        if (update) {
            AppData::Instance().medic_list.updateMedicById(id, fname, lname1, lname2, email, phone, spec, AppData::Instance().userId);
        }
        else {

            AppData::Instance().medic_list.addMedic(id, fname, lname1, lname2, email, phone, spec, AppData::Instance().userId);
        }

        return TRUE;
    }

inline void removeMedic() {
    std::string id;
    id = ReadTextBox(IDC_TXT_MED_CEDULA);
    bool isDeleted = AppData::Instance().medic_list.removeMedicById(id);
    ClearMedicFields();
    if (isDeleted) {
	    MessageBox(AppData::Instance().activeWindow, L"Registro eliminado!", L"Info", MB_OK);
    }
}

inline void searchMedic() {
    std::string id;
    id =  ReadTextBox(IDC_TXT_MED_CEDULA);
    
    // BINARY SEARCH
    MedicNode* found =  searchMedicById(id);

    if (!found) {
        ClearMedicFields();
		MessageBox(AppData::Instance().activeWindow, L"Cedula no registrada!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }
    SetTextBox(IDC_TXT_MED_CEDULA, found->id);
    SetTextBox(IDC_TXT_MED_NOMBRE, found->fname);
    SetTextBox(IDC_TXT_MED_AP_PATERNO, found->lname1);
    SetTextBox(IDC_TXT_MED_AP_MATERNO, found->lname2);
    SetTextBox(IDC_TXT_MED_CORREO, found->email);
    SetTextBox(IDC_TXT_MED_TELEFONO, found->phone);
    SetComboBoxByString(IDC_CBX_MED_ESPECIAL, found->spec);

}

inline INT_PTR CALLBACK WindowProcMedic(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    HWND hCombo;
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
		hCombo = GetDlgItem(hDlg, IDC_CBX_MED_ESPECIAL);
        FillSpecialtyComboBox(hCombo);
        return TRUE;

    case WM_COMMAND:
        bool success;
        switch (LOWORD(wParam)) {
        case IDC_BTN_MED_AGREGAR:
            success = AddMedic(false);
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

        case IDC_BTN_MED_MODIFICAR:
            success = AddMedic(true);
            if (success) {
	            MessageBox(hDlg, L"Registro modificado!", L"Info", MB_OK);
            }
            return TRUE;

        case IDC_BTN_MED_CONSULTAR:
            searchMedic();
            return TRUE;

        case IDC_BTN_MED_ELIMINAR:
            removeMedic();
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }

    return FALSE;
}
