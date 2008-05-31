#include "stdafx.h"
#include "lab12.h"

const int XSIZE = 400;
const int YSIZE = 400;

bool alive = true;
HWND hMainWnd;

HBRUSH hLeftBrush, hRightBrush;			// дескрипторы кистей для закрашивания окна
HBRUSH hCircle1Brush, hCircle2Brush;	// дескрипторы кистей для рисования круга
HPEN hRectPen;							// дескриптор пера для рисования квадрата
bool CurrentCircle;

int rect_sz = 50;	// размер квадрата
int rect_min = 20;
int rect_max = 80;
int dr = 5;			// шаг изменения размера квадрата

// главная функция WinMain
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	LPCWSTR szClassName = L"mainWindow";
	LPCWSTR szTitle = L"Потоки";

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szClassName;
	RegisterClass(&wc);						// зарегистрируем класс главного окна

	hMainWnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW, XSIZE, YSIZE/2,
							XSIZE+8, YSIZE+34, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hMainWnd, SW_SHOWNORMAL);	// создадим главное окно и сделаем его видимым

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))	// организуем цикл обработки сообщений
		DispatchMessage(&msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE,  OnCreate);		// обработка сообщения WM_CREATE
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);	// обработка сообщения WM_COMMAND
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);	// обработка сообщения WM_DESTROY
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT)
{
	hLeftBrush  = CreateSolidBrush(RGB(200, 255, 200));	// создание кисти для левой половины окна
	hRightBrush = CreateSolidBrush(RGB(200, 200, 255));	// создание кисти для правой половины окна

	hCircle1Brush = CreateSolidBrush(RGB(198, 255, 0));
	hCircle2Brush = CreateSolidBrush(RGB(255, 0, 198));

	hRectPen = CreatePen(PS_SOLID, 20, RGB(255, 0, 0));	// создание пера для квадрата

	DWORD id;
	CreateThread(NULL, 0, Thread1, NULL, 0, &id);
	CreateThread(NULL, 0, Thread2, NULL, 0, &id);
	CreateThread(NULL, 0, Thread3, NULL, 0, &id);
	CreateThread(NULL, 0, Thread4, NULL, 0, &id);

	return TRUE;
}

// Обработка сообщения OnCommand
void OnCommand(HWND hwnd, int id, HWND, UINT)
{
	switch (id)		// какой пункт меню был выбран
	{
	case ID_MIN10:	rect_min =  10;	rect_sz =  10;	dr =  5;	break;
	case ID_MIN20:	rect_min =  20;	rect_sz =  20;	dr =  5;	break;
	case ID_MIN50:	rect_min =  50;	rect_sz =  50;	dr =  5;	break;
	case ID_MAX60:	rect_max =  60;	rect_sz =  60;	dr = -5;	break;
	case ID_MAX80:	rect_max =  80;	rect_sz =  80;	dr = -5;	break;
	case ID_MAX100:	rect_max = 100;	rect_sz = 100;	dr = -5;	break;
	}
}

void OnDestroy(HWND hwnd)
{
	alive = false;

	DeleteBrush(hLeftBrush);
	DeleteBrush(hRightBrush);
	DeleteBrush(hCircle1Brush);
	DeleteBrush(hCircle2Brush);
	DeletePen(hRectPen);		// удаление кистей и пера
	PostQuitMessage(0);
}

DWORD WINAPI Thread1(LPVOID)
{
	while (alive)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		RECT rect;
		GetClientRect(hMainWnd, &rect);
		int l = rect.left,
			t = rect.top,
			r = (rect.right >> 1) + 1,
			b = (rect.bottom >> 1) + 1;

		HDC hdc = GetDC(hMainWnd);
		SetBkMode(hdc, TRANSPARENT);

		SelectPen(hdc, GetStockPen(NULL_PEN));
		SelectBrush(hdc, hLeftBrush);
		Rectangle(hdc, l, t, r, b);

		WCHAR szTime[3];

		wsprintf(szTime, L"%02d", st.wHour);
		SetTextColor(hdc, RGB(st.wHour*10,0,0));
		TextOut(hdc, 20, 20, szTime, wcslen(szTime));

		wsprintf(szTime, L":");
		SetTextColor(hdc, RGB(0,0,0));
		TextOut(hdc, 40, 20, szTime, wcslen(szTime));

		wsprintf(szTime, L"%02d", st.wMinute);
		SetTextColor(hdc, RGB(0,st.wMinute*4,0));
		TextOut(hdc, 50, 20, szTime, wcslen(szTime));

		wsprintf(szTime, L":");
		SetTextColor(hdc, RGB(0,0,0));
		TextOut(hdc, 70, 20, szTime, wcslen(szTime));

		wsprintf(szTime, L"%02d", st.wSecond);
		SetTextColor(hdc, RGB(0,0,st.wSecond*4));
		TextOut(hdc, 80, 20, szTime, wcslen(szTime));

		ReleaseDC(hMainWnd, hdc);

		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI Thread2(LPVOID)
{
	while (alive)
	{
		RECT rect;
		GetClientRect(hMainWnd, &rect);
		int l = rect.right >> 1,
			t = rect.bottom >> 1,
			r = rect.right,
			b = rect.bottom;

		HDC hdc = GetDC(hMainWnd);

		SelectPen(hdc, GetStockPen(NULL_PEN));
		SelectBrush(hdc, hRightBrush);
		Rectangle(hdc, l, t, r, b);

		if (CurrentCircle)
			SelectBrush(hdc, hCircle1Brush);
		else
			SelectBrush(hdc, hCircle2Brush);
		Ellipse(hdc, rect.right-70, rect.bottom-70, rect.right-20, rect.bottom-20);

		ReleaseDC(hMainWnd, hdc);

		CurrentCircle = !CurrentCircle;
		Sleep(500);
	}

	return 0;
}

DWORD WINAPI Thread3(LPVOID)
{
	while (alive)
	{
		RECT rect;
		GetClientRect(hMainWnd, &rect);
		int l = rect.right >> 1,
			t = rect.top,
			r = rect.right,
			b = (rect.bottom >> 1) + 1;

		HDC hdc = GetDC(hMainWnd);						// получение контекста устройства

		SelectPen(hdc, GetStockPen(NULL_PEN));			// выбор прозрачного пера
		SelectBrush(hdc, hRightBrush);					// выбор кисти
		Rectangle(hdc, l, t, r, b);

		SelectPen(hdc, hRectPen);						// выбор пера квадрата
		SelectBrush(hdc, GetStockBrush(NULL_BRUSH));	// выбираем прозрачную кисть
		l += (r - l) >> 1;
		t += (b - t) >> 1;
		Rectangle(hdc, l - rect_sz, t - rect_sz, l + rect_sz, t + rect_sz);	// рисование квадрата

		ReleaseDC(hMainWnd, hdc);

		rect_sz += dr;		// увеличить размер квадрата

		if (rect_sz > rect_max || rect_sz < rect_min)
			dr = -dr;	// переключение: уменьшение или увеличение квадрата

		Sleep(100);
	}

	return 0;
}

DWORD WINAPI Thread4(LPVOID)
{
	while (alive)
	{
		RECT rect;
		GetClientRect(hMainWnd, &rect);
		int l = rect.left,
			t = rect.bottom >> 1,
			r = (rect.right >> 1) + 1,
			b = rect.bottom;

		HDC hdc = GetDC(hMainWnd);
		SetBkMode(hdc, TRANSPARENT);

		SelectPen(hdc, GetStockPen(NULL_PEN));
		SelectBrush(hdc, hLeftBrush);
		Rectangle(hdc, l, t, r, b);

		WCHAR szText[5];
		if (GetAsyncKeyState(VK_LBUTTON))
			wsprintf(szText, L"DOWN");
		else
			wsprintf(szText, L"UP");

		TextOut(hdc, r - 100, t + 10, szText, wcslen(szText));

		ReleaseDC(hMainWnd, hdc);

		Sleep(100);
	}

	return 0;
}
