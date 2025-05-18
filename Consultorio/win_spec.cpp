#include "data.h"

inline void UpdateSpecFields(HWND hList) {
    SetTextBox(IDC_TXT_ESP_EDICION, "");
	FillSpecialtyListBox(hList);
}

inline BOOL AddSpec(HWND hList) {
	std::string spec = ReadTextBox(AppData::Instance().activeWindow, IDC_TXT_ESP_EDICION);
	if (IsEmpty(spec)) {
		return FALSE;
	}

	AppData::Instance().spec_list.addSpec(spec, spec, AppData::Instance().userId);
    UpdateSpecFields(hList);
	return TRUE;
}

inline void removeSpec(HWND hList) {
	std::string spec = ReadTextBox(AppData::Instance().activeWindow, IDC_TXT_ESP_EDICION);

    int index = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);

    if (index != LB_ERR) {
        wchar_t buffer[256];
        SendMessage(hList, LB_GETTEXT, index, (LPARAM)buffer);
        std::string selectedItem = wcharToChar(buffer);

		bool isDeleted = AppData::Instance().spec_list.removeSpecById(selectedItem);
		UpdateSpecFields(hList);
		if (isDeleted) {
			MessageBox(AppData::Instance().activeWindow, L"Especialidad eliminada!", L"Info", MB_OK);
		}
    }
}

inline INT_PTR CALLBACK WindowProcSpec(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND hList;
    switch (message) {
    case WM_INITDIALOG:
        AppData::Instance().activeWindow = hDlg;
        CenterWindow(hDlg);
        hList = GetDlgItem(hDlg, IDC_TXT_ESP);
        FillSpecialtyListBox(hList);
        return TRUE;

    case WM_COMMAND:
        bool success;
        switch (LOWORD(wParam)) {
        case IDC_BTN_ESP_AGREGAR:
			hList = GetDlgItem(hDlg, IDC_TXT_ESP);
            success = AddSpec(hList);
            if (success) {


	            MessageBox(hDlg, L"Especialidad registrada!", L"Info", MB_OK);
            }
            else {

			MessageBox(hDlg, L"Campos vacios!", L"Error", MB_OK | MB_ICONERROR);
            }
            return TRUE;

        case IDC_BTN_ESP_ELIMINAR:
            hList = GetDlgItem(hDlg, IDC_TXT_ESP);
            removeSpec(hList);
            return TRUE;

        case IDC_BTN_ESP_REGRESAR:
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
