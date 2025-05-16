//ESTA ES OTRA VERSION DE LA VENTANA REPORTE, SI ES NECESARIO BORRA LA ANTERIOR


#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define ID_COMBO_ESPECIALIDAD 1001
#define ID_COMBO_MEDICO       1002
#define ID_EDIT_FECHA_INI     1003
#define ID_EDIT_FECHA_FIN     1004
#define ID_BUTTON_BUSCAR      1005
#define ID_LISTVIEW_REPORTE   1006


LRESULT CALLBACK ReporteMedicosProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hComboEspecialidad, hComboMedico, hEditFechaIni, hEditFechaFin, hButtonBuscar, hListView;

    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(L"static", L"Especialidad:", WS_VISIBLE | WS_CHILD,
            20, 20, 100, 20, hWnd, NULL, NULL, NULL);

        hComboEspecialidad = CreateWindowW(L"combobox", NULL,
            CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            120, 20, 200, 100, hWnd, (HMENU)ID_COMBO_ESPECIALIDAD, NULL, NULL);

        CreateWindowW(L"static", L"Medico:", WS_VISIBLE | WS_CHILD,
            20, 60, 100, 20, hWnd, NULL, NULL, NULL);

        hComboMedico = CreateWindowW(L"combobox", NULL,
            CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            120, 60, 200, 100, hWnd, (HMENU)ID_COMBO_MEDICO, NULL, NULL);

        CreateWindowW(L"static", L"Fecha inicial:", WS_VISIBLE | WS_CHILD,
            20, 100, 100, 20, hWnd, NULL, NULL, NULL);

        hEditFechaIni = CreateWindowW(L"edit", NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            120, 100, 100, 20, hWnd, (HMENU)ID_EDIT_FECHA_INI, NULL, NULL);

        CreateWindowW(L"static", L"Fecha final:", WS_VISIBLE | WS_CHILD,
            240, 100, 100, 20, hWnd, NULL, NULL, NULL);

        hEditFechaFin = CreateWindowW(L"edit", NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            340, 100, 100, 20, hWnd, (HMENU)ID_EDIT_FECHA_FIN, NULL, NULL);

        hButtonBuscar = CreateWindowW(L"button", L"Buscar",
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            460, 95, 80, 25, hWnd, (HMENU)ID_BUTTON_BUSCAR, NULL, NULL);

        //LISTVIEW 
        INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
        InitCommonControlsEx(&icex);

        hListView = CreateWindowW(WC_LISTVIEW, L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
            20, 140, 760, 300,
            hWnd, (HMENU)ID_LISTVIEW_REPORTE, NULL, NULL);

        LVCOLUMN lvc = { 0 };
        lvc.mask = LVCF_TEXT | LVCF_WIDTH;

        const wchar_t* headers[] = { L"Cedula", L"Nombre", L"Fecha", L"Dia", L"Hora", L"Paciente", L"Estatus", L"Diagnostico" };
        int widths[] = { 80, 120, 80, 60, 60, 120, 100, 140 };

        for (int i = 0; i < 8; ++i) {
            lvc.pszText = (LPWSTR)headers[i];
            lvc.cx = widths[i];
            ListView_InsertColumn(hListView, i, &lvc);
        }
    } break;

    case WM_COMMAND://NO ESTA IMPLEMETADO NO SUPE COMO 
        if (LOWORD(wParam) == ID_BUTTON_BUSCAR) {
            MessageBox(hWnd, L"Buscar", L"Info", MB_OK);
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void MostrarVentanaReporteMedico(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"ReporteMedicoClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = ReporteMedicosProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    CreateWindowEx(0, CLASS_NAME, L"Reporte de Medico",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        100, 100, 820, 500,
        NULL, NULL, hInstance, NULL);
}
