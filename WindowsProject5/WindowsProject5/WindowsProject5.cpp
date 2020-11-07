// WindowsProject5.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject5.h"

#define MAX_LOADSTRING 100
#define MYDISPLAY 1

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

typedef struct tagMYREC
{
	int  color;
	int  type;
} MYCOMBO;

MYCOMBO MyCombo;
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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5);
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
//  WM_PAINT    - qОтрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

BOOL checked;
COPYDATASTRUCT MyCDS;
int firstRadioGroup = 0, secondRadioGroup = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hGrpButtons;
	
	
    switch (message)
    {
	case WM_CREATE:
		{
		//First radio group 
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Red",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
			10, 220,
			300, 20,
			hWnd, //<----- Use main window handle
			(HMENU)101,
			hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Blue",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			10, 245,
			300, 20,
			hWnd,
			(HMENU)102,
			hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Green",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			10, 270,
			300, 20,
			hWnd,
			(HMENU)103,
			hInst, NULL);


			//Second radio group 
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Star",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
			350, 220,
			300, 20,
			hWnd, //<----- Use main window handle
			(HMENU)201,
			hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Circle",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			350, 245,
			300, 20,
			hWnd,
			(HMENU)202,
			hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Square",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			350, 270,
			300, 20,
			hWnd,
			(HMENU)203,
			hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Rhombus",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			350, 295,
			300, 20,
			hWnd,
			(HMENU)204,
			hInst, NULL);
		}

		CreateWindow(TEXT("button"), TEXT("Draw"),
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			20, 20, 185, 35,
			hWnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CheckDlgButton(hWnd, 1, BST_UNCHECKED);
    	
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case 1:
				checked = IsDlgButtonChecked(hWnd, 1);
				MyCombo.color = firstRadioGroup;
				MyCombo.type = secondRadioGroup;
				if (checked) {
					CheckDlgButton(hWnd, 1, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 1, BST_CHECKED);
					MyCDS.dwData = MYDISPLAY;          // function identifier
					MyCDS.cbData = sizeof(MyCombo);  // size of data
					MyCDS.lpData = &MyCombo;          // function identifier
					HWND hwDispatch = FindWindow(L"WINDOWSPROJECT5SECOND", L"WindowsProject5-Second");
					if (hwDispatch != NULL)
						SendMessage(hwDispatch,
							WM_COPYDATA,
							(WPARAM)(HWND)hWnd,
							(LPARAM)(LPVOID)&MyCDS);
					else
						MessageBox(hWnd, L"Can't send WM_COPYDATA", L"WindowsProject5-Second", MB_OK);
				}
				break;
			case 101:
				firstRadioGroup = 1;
				break;

			case 102:
				firstRadioGroup = 2;
				break;

			case 103:
				firstRadioGroup = 3;
				break;

			case 201:
				secondRadioGroup = 1;
				break;
			case 202:
				secondRadioGroup = 2;
				break;
			case 203:
				secondRadioGroup = 3;
				break;
			case 204:
				secondRadioGroup = 4;
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
