// WindowsProject5-Second.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject5-Second.h"

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

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
PCOPYDATASTRUCT pMyCDS;

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5SECOND, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5SECOND));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5SECOND));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5SECOND);
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
MYCOMBO MyCombo;

void selectBrushColor(HDC hdc, int color)
{
	HBRUSH hBrush;
	if (color == 1)
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
	}
	else if (color == 2)
	{
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
	}
	else
	{
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hBrush);
}

void drawFigure(HDC hdc, int type, int x, int y)
{
	if (type == 1)
	{
		POINT polygon[] = { {x, y - 30},{x + 30, y}, {x + 15, y + 30}, {x - 15, y + 30}, {x - 30 , y}};
		Polygon(hdc, polygon, sizeof(polygon) / sizeof(polygon[0]));
	}
	else if (type == 3)
	{
		POINT polygon[] = { {x - 30, y - 30},{x + 30, y - 30}, {x + 30, y + 30}, {x - 30, y + 30} };
		Polygon(hdc, polygon, sizeof(polygon) / sizeof(polygon[0]));
	}
	else if (type == 2)
	{
		Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);
	}
	else
	{
		POINT polygon[] = { {x - 60, y},{x, y - 30}, {x + 60, y}, {x, y + 30} };
		Polygon(hdc, polygon, sizeof(polygon) / sizeof(polygon[0]));
	}
}
int mouseX, mouseY;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int result;
    switch (message)
    {
	case WM_COPYDATA:
		pMyCDS = (PCOPYDATASTRUCT)lParam;
		switch (pMyCDS->dwData)
		{
			case MYDISPLAY:
				MyCombo.color = ((MYCOMBO *)(pMyCDS->lpData))->color;
				MyCombo.type = ((MYCOMBO *)(pMyCDS->lpData))->type;
			break;
			default:
				break;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			mouseX = LOWORD(lParam);
			mouseY = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, FALSE);
		}
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (MyCombo.type != 0) {
				selectBrushColor(hdc, MyCombo.color);
				drawFigure(hdc, MyCombo.type, mouseX, mouseY);
			}
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
