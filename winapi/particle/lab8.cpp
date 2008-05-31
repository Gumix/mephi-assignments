#include "stdafx.h"
#include "lab8.h"

int XSIZE = 400;
int YSIZE = 300;

int partSize = 16;
int partHits = 0;
double partX = 10;
double partY = 40;
int partTime = 1500;
int partSpeed = 200;
int partAngle = 20;

HINSTANCE hInstance;
HWND hwndPlain, hwndParticle, hwndDialog;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	hInstance = hInst;

	LPWSTR szClassName = L"MainWindow";
	LPWSTR szTitle = L"Моделирование движения частицы";

	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = szClassName;
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_LAB8);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = GetStockBrush(LTGRAY_BRUSH);
	RegisterClass(&wc);

	wc.lpszClassName = L"Plain";
	wc.lpfnWndProc = DefWindowProc;
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	RegisterClass(&wc);

	wc.lpszClassName = L"Particle";
	wc.lpfnWndProc = ParticleWndProc;
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
							 50, 50, 0, 0, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0))
		if (!IsDialogMessage(hwndDialog, &Msg))
			DispatchMessage(&Msg);

	return  0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT)
{
	hwndPlain = CreateWindow(L"Plain", NULL, WS_CHILD | WS_VISIBLE, 10, 10,
							 XSIZE, YSIZE, hwnd, NULL, hInstance, NULL);
	hwndParticle = CreateWindow(L"Particle", NULL, WS_CHILD | WS_VISIBLE,
								partX, partY, partSize, partSize, hwndPlain,
								NULL, hInstance, NULL);

	hwndDialog = CreateDialogParam(hInstance, (LPCWSTR)IDD_DIALOG, hwnd, DlgProc, 0);
	MoveWindow(hwndDialog, XSIZE+100, 50, 202, 620, FALSE);
	ShowWindow(hwndDialog, SW_SHOW);

	return TRUE;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, DlgOnInitDialog);
	default:
		return FALSE;
	}
}

BOOL DlgOnInitDialog(HWND hwnd, HWND, LPARAM)
{
	WCHAR szText[5];

	_itow_s(XSIZE, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_WIDTH), (LPCWSTR)szText);

	_itow_s(YSIZE, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_HEIGHT), (LPCWSTR)szText);

	_itow_s(partSize, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_SIZE), (LPCWSTR)szText);

	_itow_s(partX, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_X), (LPCWSTR)szText);

	_itow_s(partY, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_Y), (LPCWSTR)szText);

	_itow_s(partTime/100, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_TIME), (LPCWSTR)szText);

	_itow_s(partSpeed, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_SPEED), (LPCWSTR)szText);

	_itow_s(partAngle, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT_ANGLE), (LPCWSTR)szText);

	return TRUE;
}

void DlgGetSettings()
{
	const int MAX_TEXT = 4;

	WCHAR szText[MAX_TEXT+1];

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_WIDTH), szText, MAX_TEXT);
	XSIZE = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_HEIGHT), szText, MAX_TEXT);
	YSIZE = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_SIZE), szText, MAX_TEXT);
	partSize = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_X), szText, MAX_TEXT);
	partX = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_Y), szText, MAX_TEXT);
	partY = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_TIME), szText, MAX_TEXT);
	partTime = _wtoi(szText) * 100;

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_SPEED), szText, MAX_TEXT);
	partSpeed = _wtoi(szText);

	GetWindowText(GetDlgItem(hwndDialog, IDC_EDIT_ANGLE), szText, MAX_TEXT);
	partAngle = _wtoi(szText);
}

void OnGetMinMaxInfo(HWND, LPMINMAXINFO lpmmi)
{
	lpmmi->ptMinTrackSize.x = XSIZE + 28;
	lpmmi->ptMinTrackSize.y = YSIZE + 74;
	lpmmi->ptMaxTrackSize.x = XSIZE + 28;
	lpmmi->ptMaxTrackSize.y = YSIZE + 74;
}

void OnCommand(HWND hwnd, int id, HWND, UINT)
{
	switch (id)
	{
	case IDM_START:
		partHits = 0;

		DlgGetSettings();

		WCHAR szText[3];
		_itow_s(partTime/100, szText, 10);
		SetWindowText(GetDlgItem(hwndDialog, IDC_COUNTER), (LPCWSTR)szText);

		SendDlgItemMessage(hwndDialog, IDC_TIME_LIST, LB_RESETCONTENT, 0, 0);

		MoveWindow(hwnd, 50, 50, XSIZE + 28, YSIZE + 74, TRUE);
		MoveWindow(hwndPlain, 10, 10, XSIZE, YSIZE, TRUE);
		MoveWindow(hwndParticle, partX, partY, partSize, partSize, TRUE);

		SetTimer(hwnd, 0, 10, ResidueTimerProc);

		break;

	case IDM_EXIT:
		DestroyWindow(hwnd);
	}
}

void OnDestroy(HWND)
{
	PostQuitMessage(0);
}

LRESULT CALLBACK ParticleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_PAINT, ParticleOnPaint);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void ParticleOnPaint(HWND hwnd)
{
	WCHAR szText[5];
	_itow_s(partHits, szText, 10);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	SetTextColor(hdc, RGB(200,255,200));
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, 0, 0, szText, wcslen(szText));

	EndPaint(hwnd, &ps);
}

inline void MoveParticle()
{
	int old_partHits = partHits;

	double a = partAngle * M_PI / 180;

	int new_x = partX + partSpeed * cos(a) / 100 + 0.5;
	int new_y = partY + partSpeed * sin(a) / 100 + 0.5;

	if ((new_x < 0) || (new_x+partSize > XSIZE))
	{
		partAngle = 180 - partAngle;
		partHits++;
	}
	else if ((new_y < 0) || (new_y+partSize > YSIZE))
	{
		partAngle = 360 - partAngle;
		partHits++;
	}

	if (partHits > old_partHits)
	{
		a = partAngle * M_PI / 180;

		MessageBeep(MB_OK);

		SYSTEMTIME st;
		GetLocalTime(&st);

		WCHAR szText[20];
		wsprintf((LPWSTR)szText, L"%d - %02d:%02d:%02d.%03d", partHits,
				 st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		SendDlgItemMessage(hwndDialog, IDC_TIME_LIST, LB_ADDSTRING, 0, (LPARAM)szText);
	}

	partX += partSpeed * cos(a) / 100;
	partY += partSpeed * sin(a) / 100;

	MoveWindow(hwndParticle, partX+0.5, partY+0.5, partSize, partSize, TRUE);

	InvalidateRect(hwndPlain, NULL, TRUE);
}

void CALLBACK ResidueTimerProc(HWND hwnd, UINT, UINT, DWORD)
{
	partTime--;

	MoveParticle();

	if (!(partTime%100))
	{
		WCHAR szText[3];
		_itow_s(partTime/100, szText, 10);
		SetWindowText(GetDlgItem(hwndDialog, IDC_COUNTER), (LPCWSTR)szText);
	}

	if (partTime <= 0)
		KillTimer(hwnd, 0);
}
