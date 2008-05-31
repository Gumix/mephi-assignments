#include "stdafx.h"
#include "proc2.h"

int n = 5;
int l = 100;
int color = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	WCHAR szClassName[] = L"p2Window";
	WCHAR szTitle[] = L"Процесс 2";
	MSG Msg;
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszClassName = szClassName;
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
							 300, 100, 400, 400, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, NULL, 0, 0))
		DispatchMessage(&Msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_COPYDATA, OnCopyData);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void OnDestroy(HWND)
{
	PostQuitMessage(0);
}

BOOL OnCopyData(HWND hwnd, HWND, COPYDATASTRUCT *pcds)
{
	LPINT p = LPINT(pcds->lpData);
	n = p[0];
	l = p[1];
	color = p[2];

	InvalidateRect(hwnd, NULL, TRUE);

	return TRUE;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	HPEN hPen = CreatePen(PS_SOLID, 5, color);
	SelectPen(hdc, hPen);

	double a = 0;
	int x = 200 + l * cos(a);
	int y = 200 + l * sin(a);
	MoveToEx(hdc, x, y, NULL);

	for (int i = 1; i <= n; i++)
	{
		a = M_PI/180 * 360.0/n * i;
		x = 200 + l * cos(a);
		y = 200 + l * sin(a);
		LineTo(hdc, x, y);
	}

	DeletePen(hPen);

	EndPaint(hwnd, &ps);
}
