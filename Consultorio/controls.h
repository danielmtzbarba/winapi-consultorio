#pragma once

#include "data.h"

// TEXTBOX
inline void SetTextBox(int id, const std::string& value) {
    std::wstring wvalue = StringToWString(value);
    SetWindowTextW(GetDlgItem(AppData::Instance().activeWindow, id), wvalue.c_str());
}

inline std::string ReadTextBox(int ID_TEXTBOX) {
        wchar_t buffer[256];
        HWND hwndEdit = GetDlgItem(AppData::Instance().activeWindow, ID_TEXTBOX);
        GetWindowTextW(hwndEdit, buffer, sizeof(buffer));
        std::string str = wcharToChar(buffer);
        return str;
}

// LISTBOXES
inline void FillSpecialtyListBox(HWND hList) {
    SendMessage(hList, LB_RESETCONTENT, 0, 0);

    SpecNode* current = AppData::Instance().spec_list.head;
    while (current) {
        std::wstring wname = StringToWString(current->name); // Use the utility!
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)wname.c_str());
        current = current->next;
    }
}

inline void FillRoomsListBox(HWND hList, std::string spec) {
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    std::vector<std::string> foundRooms = AppData::Instance().room_list.getRoomIdsBySpec(spec);
    for (const auto& id : foundRooms) {
        std::wstring wname = StringToWString(id); // Use the utility!
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)wname.c_str());
    }
}

// COMBOBOXES
inline void FillSpecialtyComboBox(HWND hCombo) {
    SendMessage(hCombo, CB_RESETCONTENT, 0, 0);

    SpecNode* current = AppData::Instance().spec_list.head;
    while (current) {
        std::wstring wname = StringToWString(current->name); // Use the utility!
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)wname.c_str());
        current = current->next;
    }
}

inline void FillPatientComboBox(HWND hCombo) {
    SendMessage(hCombo, CB_RESETCONTENT, 0, 0);

    PatientNode* current = AppData::Instance().patient_list.head;
    while (current) {
        std::wstring wname = StringToWString(current->id); // Use the utility!
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)wname.c_str());
        current = current->next;
    }
}

inline void SetComboBoxByString(int id, const std::string& value) {
    HWND hCombo = GetDlgItem(AppData::Instance().activeWindow, id);
    std::wstring wvalue = StringToWString(value);
    SendMessage(hCombo, CB_SELECTSTRING, -1, (LPARAM)wvalue.c_str());
}

//DATE
inline std::string readDate(const int datecontrol_id) {
    SYSTEMTIME st = { 0 };
    HWND hDatePicker = GetDlgItem(AppData::Instance().activeWindow, datecontrol_id);
    std::string date_str;
    if (SendMessage(hDatePicker, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
        // Now `st` contains the selected date/time.
        // Example: convert to string
        wchar_t buffer[100];
        swprintf(buffer, 100, L"%02d-%02d-%04d", st.wDay, st.wMonth, st.wYear);
        date_str = wstringToString(buffer);
    }
    return date_str;
}

// LISTVIEW
inline void FillListView(HWND hListView, int row, std::wstring rowData[]) {
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.iItem = static_cast<int>(row);
	lvi.pszText = const_cast<LPWSTR>(rowData[0].c_str());
	ListView_InsertItem(hListView, &lvi);

	for (int j = 1; j < 8; ++j) {
		LVITEM subItem = { 0 };
		subItem.iSubItem = j;
		subItem.iItem = static_cast<int>(row);
		subItem.mask = LVIF_TEXT;
		subItem.pszText = const_cast<LPWSTR>(rowData[j].c_str());
		ListView_SetItem(hListView, &subItem);
	}
}

inline void drawListView(int control_id, const wchar_t* headers[], int widths[]) {
    HWND hListView;
	INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&icex);

	hListView = CreateWindowW(WC_LISTVIEW, L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
		80, 160, 760, 300,
		AppData::Instance().activeWindow, (HMENU)control_id, NULL, NULL);

	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;

	for (int i = 0; i < 8; ++i) {
		lvc.pszText = (LPWSTR)headers[i];
		lvc.cx = widths[i];
		ListView_InsertColumn(hListView, i, &lvc);
	}
}

// CLEAN FIELDS
inline void CleanReportFields(bool medreport) {
    HWND hComboSpec = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_REPMED_ESPECIALIDAD);
    HWND hComboMed = GetDlgItem(AppData::Instance().activeWindow, IDC_CBX_CIT_MEDICO);
    HWND hListView = GetDlgItem(AppData::Instance().activeWindow, ID_LISTVIEW_REPORTE); 

    if (medreport) {
        SendMessage(hComboMed, CB_RESETCONTENT, 0, 0);
    }

    if (hComboMed) {
        SendMessage(hComboMed, CB_SETCURSEL, -1, 0); // Deselect any selection
    }

    if (hComboSpec) {
        SendMessage(hComboSpec, CB_SETCURSEL, -1, 0); // Deselect any selection
    }

    ListView_DeleteAllItems(hListView);
}

// Windows
inline void CenterWindow() {
    RECT rc;
    GetWindowRect(AppData::Instance().activeWindow, &rc);

    int winWidth = rc.right - rc.left;
    int winHeight = rc.bottom - rc.top;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = (screenWidth - winWidth) / 2;
    int y = (screenHeight - winHeight) / 2;

    MoveWindow(AppData::Instance().activeWindow, x, y, winWidth, winHeight, TRUE);
}
