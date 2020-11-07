// WindowsProject3.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject3.h"
#include "time.h"

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
void Draw_LeftRightBottom_Rectangles(RECT rect, HDC hdc, HBRUSH brush, int width, int height);
void DrawClearButton(HDC hdc);
void DrawPaintButton(HDC hdc);

bool isPainting = false;
BOOL isMouseDownOnClearButton = FALSE;
BOOL isMouseDownOnPaintButton = FALSE;
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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
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
void drawLine(HDC hdc, HWND hWnd, int x_start, int y_start, int x_end, int y_end)
{
	
	MoveToEx(hdc, x_start, y_start, NULL);
	LineTo(hdc, LOWORD(x_end), HIWORD(y_end));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND paint_button, clear_button;
	LPDRAWITEMSTRUCT pdis;
	int clearChoice = 0, paintChoice = 0;
	
	switch (message)
	{
	case WM_CREATE:
	{
		paint_button = CreateWindow(TEXT("button"), TEXT(""),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			350, 500, 260, 80, hWnd, (HMENU)ID_PAINT,
			hInst, NULL);

		clear_button = CreateWindow(TEXT("button"), TEXT(""),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			700, 500, 260, 80, hWnd, (HMENU)ID_CLEAR,
			hInst, NULL);
	}
	break;
	
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		if (isPainting)
		{
			for (int i = 0; i < 5; i++)
			{
				srand(i + 5);
				HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(hdc, hBrush);
				Ellipse(hdc, rand() % 1200, rand() % 800, rand() % 1200, rand() % 800);

				DeleteObject(hBrush);
			}
			for (int i = 0; i < 5; i++)
			{
				srand(i + 10);
				HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(hdc, hBrush);
				int x = rand() % 1200, y = rand() % 1000, width = rand() % 300, height = rand() % 300;
				POINT vertices[] = { {x, y},{x + width, y}, {x + width, y - height}, {x, y - height} };
				Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
				DeleteObject(hBrush);

				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(hdc, hBrush);
				x = rand() % 500 + 300, y = rand() % 500 + 100, width = rand() % 150, height = rand() % 150;
				POINT triangle[] = { {x, y},{x + width, y + height}, {x + 2 * width, y}, {x, y} };
				Polygon(hdc, triangle, sizeof(triangle) / sizeof(triangle[0]));
				DeleteObject(hBrush);

				srand(i + 10);
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(hdc, hBrush);
				POINT polygon[] = { {rand() % 600 + 800, rand() % 600},{rand() % 600 + 800, rand() % 600}, {rand() % 600 + 800, rand() % 600}, {rand() % 600 + 800, rand() % 600 + 500} };
				Polygon(hdc, polygon, sizeof(polygon) / sizeof(polygon[0]));
				DeleteObject(hBrush);
			}
			for (int i = 0; i < 5; i++)
			{
				srand(i);
				HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
				SelectObject(hdc, hPen);
				drawLine(hdc, hWnd, rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000);
				Arc(hdc, rand() % 600, rand() % 600, rand() % 600, rand() % 600, rand() % 600, rand() % 600, rand() % 600, rand() % 600);
				DeleteObject(hPen);
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DRAWITEM:
	{
		pdis = (LPDRAWITEMSTRUCT)lParam;

		switch (pdis->CtlID)
		{
		case ID_PAINT:
		{
			DrawPaintButton(pdis->hDC);
			if (pdis->itemState && ODS_SELECTED)
			{
				isMouseDownOnPaintButton = TRUE;
			}
			else
			{
				isMouseDownOnPaintButton = FALSE;
			}
			break;
		}
		case ID_CLEAR:
		{
			DrawClearButton(pdis->hDC);
			if (pdis->itemState && ODS_SELECTED)
			{
				isMouseDownOnClearButton = TRUE;
			}
			else
			{
				isMouseDownOnClearButton = FALSE;
			}
			break;
		}
		}
			
	}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_PAINT:
		{
			paintChoice = MessageBox(hWnd, TEXT("Application activity"), TEXT("PAINTING?"), MB_OKCANCEL);
			if (paintChoice == 1)
			{
				isPainting = true;
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		break;
		case ID_CLEAR:
		{
			clearChoice = MessageBox(hWnd, TEXT("Application activity"), TEXT("CLEAR?"), MB_OKCANCEL);
			if (clearChoice == 1)
			{
				isPainting = false;
				InvalidateRect(hWnd, NULL, TRUE);
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

void DrawClearButton(HDC hdc)
{
	if (isMouseDownOnClearButton)
	{
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = 260;
		rc.bottom = 80;
		HBRUSH br = CreateSolidBrush(RGB(200, 30, 30));
		FillRect(hdc, &rc, br);

		SetBkColor(hdc, RGB(200, 30, 30));
		SetTextColor(hdc, RGB(255, 255, 255));

		TextOut(hdc, 110, 35, L"CLEAR", 5);
	}
	else
	{
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = 260;
		rc.bottom = 80;
		HBRUSH br = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(hdc, &rc, br);

		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255));

		TextOut(hdc, 110, 35, L"CLEAR", 5);
	}

}

void DrawPaintButton(HDC hdc)
{
	if (isMouseDownOnPaintButton)
	{
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = 260;
		rc.bottom = 80;
		HPEN hpen;

		//draw gradient button  
		for (int i = 0; i < 80; i++)
		{
			hpen = CreatePen(PS_SOLID, 4, RGB(150 - i, 0, 0));
			SelectObject(hdc, hpen);
			Rectangle(hdc, 0, 0 + i, 262, 1 + i);
			DeleteObject(hpen);
		}

		SetBkColor(hdc, RGB(130, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 110, 35, L"PAINT", 5);
	}
	else
	{
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = 260;
		rc.bottom = 80;
		HPEN hpen;

		//draw gradient button  
		for (int i = 0; i < 80; i++)
		{
			hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 150 - i));
			SelectObject(hdc, hpen);
			Rectangle(hdc, 0, 0 + i, 262, 1 + i);
			DeleteObject(hpen);
		}

		SetBkColor(hdc, RGB(0, 0, 130));
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 110, 35, L"PAINT", 5);
		
	}

}
