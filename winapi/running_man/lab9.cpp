#include "stdafx.h"
#include "lab9.h"

#pragma comment(lib, "winmm.lib")

const int XSIZE = 582;
const int YSIZE = 291;

const int DELAY = 10;
const int STEP = 10;

HINSTANCE hInstance;
HANDLE hGlobMem;
BITMAP bmMan;
HBITMAP hBitmap, hBitmapBg, hBitmapM1, hBitmapM2, hBitmapM3, hBitmapM4;
HDC hdcMemRes, hdcMemBg, hdcMemM1, hdcMemM2, hdcMemM3, hdcMemM4;
HDC *phdcMemMan[] = { &hdcMemM1, &hdcMemM2, &hdcMemM3, &hdcMemM4 };

int StepCounter = 0;
int iMan = 0;
int iGoBack = 0;
double t = 0;
double dt = 0.005;

int b1x[] = { 100,	150,	350,	400	};
int b1y[] = { 200,	50,		25,		125 };
int b2x[] = { 400,	450,	500,	520 };
int b2y[] = { 125,	225,	200,	30	};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	hInstance = hInst;

	LPCWSTR szClassName = L"mainWindow";
	LPCWSTR szTitle = L"Прогулка";

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszClassName = szClassName;
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
							 150, 150, 0, 0, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT)
{
	hBitmapBg = (HBITMAP)LoadImage(hInstance, (LPCWSTR)IDB_BACKGROUND, IMAGE_BITMAP, 0, 0, 0);
	hBitmapM1 = (HBITMAP)LoadImage(hInstance, (LPCWSTR)IDB_MAN1, IMAGE_BITMAP, 0, 0, 0);
	hBitmapM2 = (HBITMAP)LoadImage(hInstance, (LPCWSTR)IDB_MAN2, IMAGE_BITMAP, 0, 0, 0);
	hBitmapM3 = (HBITMAP)LoadImage(hInstance, (LPCWSTR)IDB_MAN3, IMAGE_BITMAP, 0, 0, 0);
	hBitmapM4 = (HBITMAP)LoadImage(hInstance, (LPCWSTR)IDB_MAN4, IMAGE_BITMAP, 0, 0, 0);
	GetObject(hBitmapM1, sizeof(BITMAP), &bmMan);

	HDC hdc = GetDC(hwnd);
	hdcMemRes = CreateCompatibleDC(hdc);
	hdcMemBg = CreateCompatibleDC(hdc);
	hdcMemM1 = CreateCompatibleDC(hdc);
	hdcMemM2 = CreateCompatibleDC(hdc);
	hdcMemM3 = CreateCompatibleDC(hdc);
	hdcMemM4 = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, XSIZE, YSIZE);
	ReleaseDC(hwnd, hdc);

	SelectBitmap(hdcMemRes, hBitmap);
	SelectBitmap(hdcMemBg, hBitmapBg);
	SelectBitmap(hdcMemM1, hBitmapM1);
	SelectBitmap(hdcMemM2, hBitmapM2);
	SelectBitmap(hdcMemM3, hBitmapM3);
	SelectBitmap(hdcMemM4, hBitmapM4);

	HRSRC hWaveRes = FindResource(hInstance, MAKEINTRESOURCE(MUSIC), L"WAVE");
	hGlobMem = LoadResource(hInstance, hWaveRes);
	sndPlaySound((LPCWSTR)LockResource(hGlobMem), SND_MEMORY | SND_ASYNC | SND_LOOP);

	SetTimer(hwnd, 0, DELAY, OnTimer);

	return TRUE;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	BitBlt(hdc, 0, 0, XSIZE, YSIZE, hdcMemRes, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);
}

void OnGetMinMaxInfo(HWND, LPMINMAXINFO lpmmi)
{
	lpmmi->ptMinTrackSize.x = XSIZE + 8;
	lpmmi->ptMinTrackSize.y = YSIZE + 34;
	lpmmi->ptMaxTrackSize.x = XSIZE + 8;
	lpmmi->ptMaxTrackSize.y = YSIZE + 34;
}

void CALLBACK OnTimer(HWND hwnd, UINT, UINT, DWORD)
{
	t += dt;
	if (t > 2 || t < 0)
	{
		dt = -dt;
		iGoBack = 2 - iGoBack;
	}

	if (StepCounter++ > STEP)
	{
		StepCounter = 0;
		iMan = 1 - iMan;
	}

	int XMan = 0, YMan = 0;

	if (t < 1)
		Bezier3(b1x, b1y, &XMan, &YMan, t);
	else
		Bezier3(b2x, b2y, &XMan, &YMan, t-1);

	int scale = (YMan-YSIZE/2)/5;

	BitBlt(hdcMemRes, 0, 0, XSIZE, YSIZE, hdcMemBg, 0, 0, SRCCOPY);

	StretchBlt(hdcMemRes, XMan, YMan, bmMan.bmWidth+scale, bmMan.bmHeight+scale,
			   *phdcMemMan[iMan+iGoBack], 0, 0, bmMan.bmWidth, bmMan.bmHeight, SRCAND);

	InvalidateRect(hwnd, NULL, FALSE);
}

void OnDestroy(HWND hwnd)
{
	KillTimer(hwnd, 0);

	sndPlaySound(NULL, 0);
	FreeResource(hGlobMem);

	DeleteBitmap(hBitmap);
	DeleteBitmap(hBitmapBg);
	DeleteBitmap(hBitmapM1);
	DeleteBitmap(hBitmapM2);
	DeleteBitmap(hBitmapM3);
	DeleteBitmap(hBitmapM4);

	DeleteDC(hdcMemRes);
	DeleteDC(hdcMemBg);
	DeleteDC(hdcMemM1);
	DeleteDC(hdcMemM2);
	DeleteDC(hdcMemM3);
	DeleteDC(hdcMemM4);

	PostQuitMessage(0);
}
