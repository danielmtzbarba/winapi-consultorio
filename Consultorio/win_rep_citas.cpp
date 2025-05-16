//ESTA ES OTRA VERSION DE LA VENTANA REPORTE, SI ES NECESARIO BORRA LA ANTERIOR


#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define ID_COMBO_PACIENTE     2001
#define ID_EDIT_FECHA_INI     2002
#define ID_EDIT_FECHA_FIN     2003
#define ID_BUTTON_BUSCAR      2004
#define ID_LISTVIEW_REPORTE   2005

LRESULT CALLBACK ReportePacienteProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hComboPaciente, hEditFechaIni, hEditFechaFin, hButtonBuscar, hListView;

    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(L"static", L"Paciente:", WS_VISIBLE | WS_CHILD,
            20, 20, 100, 20, hWnd, NULL, NULL, NULL);

        hComboPaciente = CreateWindowW(L"combobox", NULL,
            CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            120, 20, 250, 100, hWnd, (HMENU)ID_COMBO_PACIENTE, NULL, NULL);

        CreateWindowW(L"static", L"Fecha inicial:", WS_VISIBLE | WS_CHILD,
            20, 60, 100, 20, hWnd, NULL, NULL, NULL);

        hEditFechaIni = CreateWindowW(L"edit", NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            120, 60, 100, 20, hWnd, (HMENU)ID_EDIT_FECHA_INI, NULL, NULL);

        CreateWindowW(L"static", L"Fecha final:", WS_VISIBLE | WS_CHILD,
            240, 60, 100, 20, hWnd, NULL, NULL, NULL);

        hEditFechaFin = CreateWindowW(L"edit", NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            340, 60, 100, 20, hWnd, (HMENU)ID_EDIT_FECHA_FIN, NULL, NULL);

        hButtonBuscar = CreateWindowW(L"button", L"Buscar",
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            460, 55, 80, 25, hWnd, (HMENU)ID_BUTTON_BUSCAR, NULL, NULL);

        //LISTVIEW
        INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
        InitCommonControlsEx(&icex);

        hListView = CreateWindowW(WC_LISTVIEW, L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
            20, 100, 860, 300,
            hWnd, (HMENU)ID_LISTVIEW_REPORTE, NULL, NULL);

        LVCOLUMN lvc = { 0 };
        lvc.mask = LVCF_TEXT | LVCF_WIDTH;

        const wchar_t* headers[] = { L"ID Paciente", L"Nombre", L"Fecha", L"Dia", L"Hora", L"Medico", L"Especialidad", L"Estatus", L"Diagnostico" };
        int widths[] = { 80, 120, 80, 60, 60, 120, 100, 100, 140 };

        for (int i = 0; i < 9; ++i) {
            lvc.pszText = (LPWSTR)headers[i];
            lvc.cx = widths[i];
            ListView_InsertColumn(hListView, i, &lvc);
        }
    } break;

    case WM_COMMAND://NO ESTA IMPLEMENTADO, NO LE SUPE JSJS
        if (LOWORD(wParam) == ID_BUTTON_BUSCAR) {
            MessageBox(hWnd, L"Buscar clicado (no implementado)", L"Info", MB_OK);
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

void MostrarVentanaReportePaciente(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"ReportePacienteClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = ReportePacienteProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    CreateWindowEx(0, CLASS_NAME, L"Reporte de Citas",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        100, 100, 920, 460,
        NULL, NULL, hInstance, NULL);
}
