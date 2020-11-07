// WindowsProject6.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject6.h"
#include "cmath"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
const double PI = 3.141592653;
bool isStart = false;


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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT6));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT6);
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
//

void drawLine(HDC hdc, HWND hWnd, int x_start, int y_start, int x_end, int y_end)
{

	MoveToEx(hdc, x_start, y_start, NULL);
	LineTo(hdc, x_end, y_end);
}

double a[2];
double startAngle[2];
HANDLE threads[2];
HANDLE Semaphore;

typedef struct pr {
	double* angle;
	double* startAngle;
	int* positionX;
	int* positionY;
	int* positionX1;
	int* positionY1;
	int centerX;
	int centerY;
	int startX_1;
	int startY_1;
	int startX_2;
	int startY_2;
	HWND hWnd;
} COMBO;

COMBO threadsData[2];

DWORD WINAPI Run(LPVOID param) {
	COMBO* data = (COMBO*)param;
	double* angle = data->angle;
	double* startAngle = data->startAngle;
	int* positionX = data->positionX;
	int* positionY = data->positionY;
	int* positionX1 = data->positionX1;
	int* positionY1 = data->positionY1;
	const int centerX = data->centerX;
	const int centerY  = data->centerY;
	const int startX_1 = data->startX_1;
	const int startY_1 = data->startY_1;
	const int startX_2 = data->startX_2;
	const int startY_2 = data->startY_2;
	
	while (isStart) {
		WaitForSingleObject(Semaphore, INFINITE);
		*startAngle += *angle;
		*positionX = (startX_1 - centerX) * cos(*startAngle) - (startY_1 - centerY) * sin(*startAngle) + centerX;
		*positionY = (startX_1 - centerX) * sin(*startAngle) + (startY_1 - centerY) * cos(*startAngle) + centerY;

		*positionX1 = (startX_2 - centerX) * cos(*startAngle) - (startY_2 - centerY) * sin(*startAngle) + centerX;
		*positionY1 = (startX_2 - centerX) * sin(*startAngle) + (startY_2 - centerY) * cos(*startAngle) + centerY;

		InvalidateRect(data->hWnd, 0, true);
		Sleep(100);
		ReleaseSemaphore(Semaphore, 1, NULL);

	}

	return NULL;
}

//DWORD WINAPI threadFunction(void* args)
//{
//	a += PI / 10;
//	x_1 = (first_x - center_x) * cos(a) - (first_y - center_y) * sin(a) + center_x;
//	y_1 = (first_x - center_x) * sin(a) + (first_y - center_y) * cos(a) + center_y;
//
//	x_2 = (second_x - center_x) * cos(a) - (second_y - center_y) * sin(a) + center_x;
//	y_2 = (second_x - center_x) * sin(a) + (second_y - center_y) * cos(a) + center_y;
//	return 0;
//}

HANDLE hThread;
DWORD threadID;
int positions1[6];
int positions2[6];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND start_button, stop_button;
	HPEN Pen;
    switch (message)
    {
	case WM_CREATE:
		{
			
			start_button = CreateWindow(TEXT("button"), TEXT("START"),
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				350, 500, 260, 80, hWnd, (HMENU)ID_START,
				hInst, NULL);

			stop_button = CreateWindow(TEXT("button"), TEXT("STOP"),
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				700, 500, 260, 80, hWnd, (HMENU)ID_STOP,
				hInst, NULL);

			positions1[0] = 100;
			positions1[2] = 300;
			positions1[1] = 100;
			positions1[3] = 300;
			positions1[4] = (positions1[0] + positions1[2]) / 2;
			positions1[5] = (positions1[1] + positions1[3]) / 2;

			positions2[0] = 500;
			positions2[2] = 700;
			positions2[1] = 300;
			positions2[3] = 300;
			positions2[4] = (positions2[0] + positions2[2]) / 2;
			positions2[5] = (positions2[1] + positions2[3]) / 2;

			a[0] = PI / 10;
			a[1] = PI / 20;
			startAngle[0] = PI / 10;
			startAngle[1] = PI / 20;
			HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
			threadsData[0] = { &a[0], &startAngle[0], positions1, &positions1[1], &positions1[2], &positions1[3], positions1[4], positions1[5], 100, 100, 300, 300, hWnd};
			threadsData[1] = { &a[1], &startAngle[1], &positions2[0], &positions2[1], &positions2[2], &positions2[3], positions2[4], positions2[5], 500, 300, 700, 300, hWnd};

			
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_START:
				{
					isStart = true;
					Semaphore = CreateSemaphore(0, 2, 2, NULL);

					for (int i = 0; i < 2; i++) {

						threads[i] = CreateThread(NULL, 0, Run,
							&threadsData[i], 0, NULL);
					}
				}
				break;
			case ID_STOP:
				{
					isStart = false;
					for (int i = 0; i < 2; i++) {
						CloseHandle(threads[i]);
					}
					CloseHandle(Semaphore);
				}
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
			Pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			SelectObject(hdc, Pen);
			drawLine(hdc, hWnd, positions1[0], positions1[1], positions1[2], positions1[3]);
			drawLine(hdc, hWnd, positions2[0], positions2[1], positions2[2], positions2[3]);
			DeleteObject(Pen);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		//KillTimer(hWnd, 222);
		for (int i = 0; i < 2; i++) {
			CloseHandle(threads[i]);
		}
		CloseHandle(Semaphore);
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
