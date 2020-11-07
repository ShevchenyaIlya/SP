// WindowsProject7.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject7.h"
#include <string>

#define MAX_LOADSTRING 100
#define MODE 1

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LPCWSTR  text_1 = L"AAAA";
LPCWSTR  text_2 = L"BBBB";
LPCWSTR  text_3 = L"CCCC";
LPCWSTR  text_4 = L"DDDD";

LPCWSTR text;

HANDLE thread1, thread2, thread3, thread4;
#if MODE == 0
	HANDLE hEvent1, hEvent2, hEvent3, hEvent4;
	DWORD WINAPI ChangeText_1();
	DWORD WINAPI ChangeText_2();
	DWORD WINAPI ChangeText_3();
	DWORD WINAPI ChangeText_4();
#else
	CRITICAL_SECTION cs;
	DWORD WINAPI ChangeText(LPWSTR* newText);
#endif

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT7));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT7));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT7);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
HWND hWnd;
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

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
RECT textRect;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		{
			#if MODE == 0
				hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
				hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
				hEvent3 = CreateEvent(NULL, FALSE, FALSE, NULL);
				hEvent4 = CreateEvent(NULL, FALSE, FALSE, NULL);
				thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText_1, &text_1, 0, NULL);
				thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText_2, &text_2, 0, NULL);
				thread3 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText_3, &text_3, 0, NULL);
				thread4 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText_4, &text_4, 0, NULL);
			#else
				InitializeCriticalSection(&cs);
				thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText, &text_1, 0, NULL);
				thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText, &text_2, 0, NULL);
				thread3 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText, &text_3, 0, NULL);
				thread4 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeText, &text_4, 0, NULL);
			#endif
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
			textRect = { 350, 350, 550, 400 };
			DrawText(hdc, text, 4, &textRect, DT_LEFT);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		#if MODE != 0
			DeleteCriticalSection(&cs);
		#endif
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

#if MODE == 0
DWORD WINAPI ChangeText_1()
{
	while (true)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		text = text_1;
		Sleep(1000);
		InvalidateRect(hWnd, NULL, TRUE);
		SetEvent(hEvent2);
	}
	return 0;
}

DWORD WINAPI ChangeText_2()
{
	while (true)
	{
		WaitForSingleObject(hEvent2, INFINITE);
		text = text_2;
		Sleep(1000);
		InvalidateRect(hWnd, NULL, TRUE);
		SetEvent(hEvent3);
	}
	return 0;
}

DWORD WINAPI ChangeText_3()
{
	while (true)
	{
		WaitForSingleObject(hEvent3, INFINITE);
		text = text_3;
		Sleep(1000);
		InvalidateRect(hWnd, NULL, TRUE);
		SetEvent(hEvent4);
	}
	return 0;
}

DWORD WINAPI ChangeText_4()
{
	while (true)
	{
		WaitForSingleObject(hEvent4, INFINITE);
		text = text_4;
		Sleep(1000);
		InvalidateRect(hWnd, NULL, TRUE);
		SetEvent(hEvent1);
	}
	return 0;
}
#else
DWORD WINAPI ChangeText(LPWSTR* newText)
{
	while (true)
	{
		if (text != *newText)
		{
			if (TryEnterCriticalSection(&cs))
			{
				text = *newText;
				Sleep(1000);
				InvalidateRect(hWnd, NULL, TRUE);
				LeaveCriticalSection(&cs);
			}
		}
	}
	return 0;
}
#endif