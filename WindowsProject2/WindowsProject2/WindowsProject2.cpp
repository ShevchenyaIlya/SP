// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwndEdit = 0;
	TCHAR buffer[1024] = {0};
	HWND hListBox1 = nullptr, hListBox2 = nullptr;
	
    switch (message)
    {
	case WM_CREATE:
		{
			HWND addButton = CreateWindow(L"BUTTON", L"ADD", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
				30, 400, 100, 60, hWnd, (HMENU)ADD_CLICK, HINSTANCE(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), NULL);
			HWND clearButton = CreateWindow(L"BUTTON", L"CLEAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				160, 400, 100, 60, hWnd, (HMENU)CLEAR_CLICK, HINSTANCE(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), NULL);
			HWND toRightButton = CreateWindow(L"BUTTON", L"TO RIGHT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				290, 400, 100, 60, hWnd, (HMENU)TO_RIGHT_CLICK, HINSTANCE(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), NULL);
			HWND deleteButton = CreateWindow(L"BUTTON", L"DELETE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				420, 400, 100, 60, hWnd, (HMENU)DELETE_CLICK, HINSTANCE(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), NULL);
			hwndEdit = CreateWindowEx(0, L"EDIT",NULL,WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOVSCROLL,
				30, 350, 490, 40,	hWnd, (HMENU)ID_EDITCHILD, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),NULL);
			hListBox1 = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL
				, 30, 30, 210, 300, hWnd, (HMENU)LISTBOX1_CLICK, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
			hListBox2 = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL
				, 270, 30, 210, 300, hWnd, (HMENU)LISTBOX2_CLICK, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case ADD_CLICK:
				{
				HWND fillEdit = GetDlgItem(hWnd, ID_EDITCHILD);
				GetWindowText(fillEdit, buffer, 1024);
				int count = SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETCOUNT, 0, 0);
				bool success = true;
				for (int i = 0; i < count; i++)
				{
					TCHAR localStorage[1024];
					SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETTEXT, i, (LPARAM)localStorage);
					if (_tcscmp(buffer, localStorage) == 0) {
						success = false;
						break;
					}

				}
				if (success) {
					SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_ADDSTRING, 0, (LPARAM)buffer);
				}
				}
				break;
			case CLEAR_CLICK:
				{

				SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_RESETCONTENT, 0, 0);
				SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_RESETCONTENT, 0, 0);
			}
			break;
			case DELETE_CLICK:
				{
				int iSelectedFirst = -1;
				int iSelectedSecond = -1;
				int count = SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETCOUNT, 0, 0);
				for (int i = 0; i < count; i++)
				{
					if (SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETSEL, i, 0) > 0)
					{
						iSelectedFirst = i;
						break;
					}
				}
				count = SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_GETCOUNT, 0, 0);
				for (int i = 0; i < count; i++)
				{
					if (SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_GETSEL, i, 0) > 0)
					{
						iSelectedSecond = i;
						break;
					}
				}
				if (iSelectedFirst != -1)
				{
					SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_DELETESTRING, iSelectedFirst, 0);
				}
				if (iSelectedSecond != -1)
				{
					SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_DELETESTRING, iSelectedSecond, 0);
				}

				}
			break;
			case TO_RIGHT_CLICK:
			{
				int count = SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETCOUNT, 0, 0);
				int iSelected = -1;
				for (int i = 0; i < count; i++)
				{
					if (SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETSEL, i, 0) > 0)
					{
						iSelected = i;
						break;
					}

				}
				TCHAR Buffer[1024] = { 0 };
				if (iSelected != -1) {
					SendMessage(GetDlgItem(hWnd, LISTBOX1_CLICK), LB_GETTEXT, iSelected, (LPARAM)Buffer);
					count = SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_GETCOUNT, 0, 0);
					bool success = true;
					for (int i = 0; i < count; i++)
					{
						TCHAR localStorage[1024];
						SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_GETTEXT, i, (LPARAM)localStorage);
						if (_tcscmp(Buffer, localStorage) == 0) {
							success = false;
							break;
						}

					}
					if (success) {
						SendMessage(GetDlgItem(hWnd, LISTBOX2_CLICK), LB_ADDSTRING, 0, (LPARAM)Buffer);
					}

				}
			}
			break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
	

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
