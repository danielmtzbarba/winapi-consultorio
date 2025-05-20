#include "data.h"
#include "controls.h"
#include "search.h"

inline bool Login(HWND hDlg) {
	const int idcFields[] = {
		IDC_TXT_LOGIN_CEDULA,
		IDC_TXT_LOGIN_PASS,
	};

	std::string fieldValues[sizeof(idcFields)/sizeof(idcFields[0])];

	// Read and check each field
    for (size_t i = 0; i < sizeof(idcFields) / sizeof(idcFields[0]); ++i) {
        fieldValues[i] = ReadTextBox(idcFields[i]);
		if (IsEmpty(fieldValues[i])) {
			MessageBox(hDlg, L"Por favor, complete todos los campos obligatorios.", L"Error", MB_OK | MB_ICONERROR);
            return FALSE;
		}
	}

	// Assign values to variables for clarity
	std::string id = fieldValues[0];
	std::string password = fieldValues[1];
    
    if (userLogin(id, password)) {
        AppData::Instance().userId = id;
        return TRUE;
    } else {
		MessageBox(hDlg, L"Usuario o contraseña incorrectos.", L"Warning", MB_OK | MB_ICONWARNING);
		return FALSE;
    }

    return FALSE;
}

inline INT_PTR CALLBACK WindowProcLogin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow();
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_LOGIN_ENTRAR:
            bool success;
            success = Login(hDlg);
            if (success) {
				EndDialog(hDlg, 0);
				DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_MENU_PRINCIPAL), NULL, WindowProcMenu);
            }
            return TRUE;

        case IDC_BTN_LOGIN_REGISTRAR:
            EndDialog(hDlg, 0);
            DialogBox(AppData::Instance().hInst, MAKEINTRESOURCE(IDD_CREACION_USUARIO), NULL, WindowProcSignUp);
            return TRUE;
        }
        break;


    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
