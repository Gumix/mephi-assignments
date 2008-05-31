#include "stdafx.h"
#include "proc1.h"

#define TIMER_PERIOD	500

int color = 0;
int delta = 5;

HINSTANCE hInstance;

#define ID_BTN	101

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	WCHAR szClassName[] = L"Process1Window";
	WCHAR szTitle[] = L"Process 1";
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszClassName = szClassName;
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
							 100, 100, 400, 400, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0))
		DispatchMessage(&Msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

bool OnCreate(HWND hwnd, LPCREATESTRUCT)
{
	CreateWindow(L"BUTTON", L"Кнопка", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				 10, 10, 60, 30, hwnd, (HMENU)ID_BTN, hInstance, NULL);

	SetTimer(hwnd, 0, TIMER_PERIOD, NULL);

	return true;
}

void OnCommand(HWND hwnd, int id, HWND, UINT)
{
	if (id == ID_BTN)
	{
		HWND hwnd2 = FindWindow(NULL, L"Process 2");
		if (!hwnd2)
			MessageBox(NULL, L"Can't find window 2", L"Error", MB_OK);
		else
		{
			COPYDATASTRUCT cds;
			cds.dwData = color;
			cds.cbData = 0;
			cds.lpData = NULL;
			SendMessage(hwnd2, WM_COPYDATA, NULL, (LPARAM)&cds);
		}
	}
}

void OnTimer(HWND hwnd, UINT)
{
	color += delta;

	if (color <= 0)
	{
		color = 0;
		delta = -delta;
	}

	if (color >= 255)
	{
		color = 255;
		delta = -delta;
	}

	InvalidateRect(hwnd, NULL, TRUE);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	HBRUSH hBrush = CreateSolidBrush(RGB(color, color, color));
	SelectBrush(hdc, hBrush);
	Ellipse(hdc, 100, 100, 300, 300);
	DeleteBrush(hBrush);

	EndPaint(hwnd, &ps);
}

void OnDestroy(HWND)
{
	PostQuitMessage(0);
}
