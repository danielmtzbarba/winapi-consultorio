#include "data.h"
#include "controls.h"

inline void UpdateSpecFields(HWND hList) {
    SetTextBox(IDC_TXT_ESP_EDICION, "");
    SetTextBox(IDC_TXT_CANTIDAD, "");
	FillSpecialtyListBox(hList);
}

inline void AddRooms(int n, std::string prefix, std::string spec) {
    // Get the first three characters of the specialty, uppercase
    for (int i = 1; i <= n; ++i) {
        std::string id = prefix + std::to_string(i);
        std::string userid = "admin";
        AppData::Instance().room_list.addRoom(id, spec, userid);
    }
}

inline BOOL AddSpec(HWND hList) {
	std::string spec = ReadTextBox(IDC_TXT_ESP_EDICION);
    std::string n_str = ReadTextBox(IDC_TXT_CANTIDAD);
    if (IsEmpty(spec) || IsEmpty(n_str)) {
		return FALSE;
	}
    std::string prefix = spec.substr(0, 3);
    prefix = ToUpper(prefix);
	AppData::Instance().spec_list.addSpec(prefix, spec, AppData::Instance().userId);
    UpdateSpecFields(hList);
    int n = StringToInt(n_str);
    AddRooms(n, prefix, spec);
	return TRUE;
}

inline void removeSpec(HWND hList) {
	std::string spec = ReadTextBox(IDC_TXT_ESP_EDICION);

    int index = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);

    if (index != LB_ERR) {
        wchar_t buffer[256];
        SendMessage(hList, LB_GETTEXT, index, (LPARAM)buffer);
        std::string selectedItem = wcharToChar(buffer);
		std::string prefix = selectedItem.substr(0, 3);
		prefix = ToUpper(prefix);

		bool isDeleted = AppData::Instance().spec_list.removeSpecById(prefix);
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
        CenterWindow();
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
