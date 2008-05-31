#include "stdafx.h"
#include "proc2.h"

int color = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	WCHAR szClassName[] = L"Process2Window";
	WCHAR szTitle[] = L"Process 2";
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
							 600, 100, 300, 200, HWND_DESKTOP, NULL, hInst, NULL);
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
	color = pcds->dwData;

	InvalidateRect(hwnd, NULL, TRUE);

	return TRUE;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	HBRUSH hBrush = CreateSolidBrush(RGB(color, color, color));
	SelectBrush(hdc, hBrush);
	Rectangle(hdc, 0, 0, 300, 200);
	DeleteBrush(hBrush);

	EndPaint(hwnd, &ps);
}
