#include "stdafx.h"
#include "resource.h"

const int XMAX = 600;
const int YMAX = 600;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnCommand(HWND, int, HWND, UINT);
bool OnCreate(HWND, LPCREATESTRUCT);
void OnPaint(HWND);
void OnDestroy(HWND);

HPEN hHourPen, hMinPen, hSecPen;
HBRUSH hWhiteBrush, hChartreuseBrush, hHeliotropeBrush, hLimeBrush,
	   hMalachiteBrush, hMintGreenBrush, hPangBrush, hPeriwinkleBrush,
	   hSchoolBusYellowBrush, hZinnwalditeBrush;
HFONT hFont16A, hFont20A, hFont24A, hFont16C, hFont20C,
	  hFont24C, hFont16T, hFont20T, hFont24T;

int swBrushColor = IDM_WHITE;
int swFontName = IDM_FONTCOURIER;
int swFontSize = 20;
int	swNumerals = IDM_ARABIC;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	char szClassName[] = "MainWindow";
	char szTitle[] = "Часы";
	MSG Msg;
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc ;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_LAB5));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_LAB5);
	wc.lpszClassName = szClassName;
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW, 10, 10,
							 XMAX+8, YMAX+54, HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, NULL, 0, 0))
		DispatchMessage(&Msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void OnCommand(HWND hwnd, int id, HWND, UINT)
{
	switch(id)
	{
	case IDM_WHITE:
		swBrushColor = IDM_WHITE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_CHARTREUSE:
		swBrushColor = IDM_CHARTREUSE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_HELIOTROPE:
		swBrushColor = IDM_HELIOTROPE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_LIME:
		swBrushColor = IDM_LIME;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_MALACHITE:
		swBrushColor = IDM_MALACHITE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_MINTGREEN:
		swBrushColor = IDM_MINTGREEN;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_PANG:
		swBrushColor = IDM_PANG;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_PERIWINKLE:
		swBrushColor = IDM_PERIWINKLE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_SCHOOLBUSYELLOW:
		swBrushColor = IDM_SCHOOLBUSYELLOW;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_ZINNWALDITE:
		swBrushColor = IDM_ZINNWALDITE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONTARIAL:
		swFontName = IDM_FONTARIAL;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONTCOURIER:
		swFontName = IDM_FONTCOURIER;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONTTIMES:
		swFontName = IDM_FONTTIMES;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONT16:
		swFontSize = 16;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONT20:
		swFontSize = 20;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_FONT24:
		swFontSize = 24;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_ARABIC:
		swNumerals = IDM_ARABIC;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_ROMAN:
		swNumerals = IDM_ROMAN;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd);
	}
}

bool OnCreate(HWND, LPCREATESTRUCT)
{
	hHourPen = CreatePen(PS_SOLID, 10, RGB(250, 0, 0));
	hMinPen  = CreatePen(PS_SOLID,  5, RGB(0, 127, 255));
	hSecPen  = CreatePen(PS_SOLID,  2, RGB(100, 255, 100));

	hWhiteBrush           = CreateSolidBrush(RGB(255, 255, 255));
	hChartreuseBrush      = CreateSolidBrush(RGB(127, 255,   0));
	hHeliotropeBrush      = CreateSolidBrush(RGB(223, 115, 255));
	hLimeBrush            = CreateSolidBrush(RGB(204, 255,   0));
	hMalachiteBrush       = CreateSolidBrush(RGB(11,  218,  81));
	hMintGreenBrush       = CreateSolidBrush(RGB(152, 255, 152));
	hPangBrush            = CreateSolidBrush(RGB(199, 252, 236));
	hPeriwinkleBrush      = CreateSolidBrush(RGB(204, 204, 255));
	hSchoolBusYellowBrush = CreateSolidBrush(RGB(255, 216,   0));
	hZinnwalditeBrush     = CreateSolidBrush(RGB(235, 194, 175));

	char lpszFace1[] = "Arial Cyr";
	char lpszFace2[] = "Courier New Cyr";
	char lpszFace3[] = "Times New Roman Cyr";

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));

	strcpy(lf.lfFaceName, lpszFace1);
	lf.lfHeight = 16;
	hFont16A = CreateFontIndirect(&lf);

	lf.lfHeight = 20;
	hFont20A = CreateFontIndirect(&lf);

	lf.lfHeight = 24;
	hFont24A = CreateFontIndirect(&lf);

	strcpy(lf.lfFaceName, lpszFace2);
	lf.lfHeight = 16;
	hFont16C = CreateFontIndirect(&lf);

	lf.lfHeight = 20;
	hFont20C = CreateFontIndirect(&lf);

	lf.lfHeight = 24;
	hFont24C = CreateFontIndirect(&lf);

	strcpy(lf.lfFaceName, lpszFace3);
	lf.lfHeight = 16;
	hFont16T = CreateFontIndirect(&lf);

	lf.lfHeight = 20;
	hFont20T = CreateFontIndirect(&lf);

	lf.lfHeight = 24;
	hFont24T = CreateFontIndirect(&lf);

	return true;
}

void ArabicNumerals(HDC hdc, int R, int H)
{
	for (int i = 1, a = 30; i <= 12; i++, a += 30)
	{
		char szText[3];
		_itoa_s(i, szText, 10);

		double radAngle = a * M_PI / 180;
		int NewX = XMAX/2 + R*sin(radAngle) - 5,
			NewY = YMAX/2 - R*cos(radAngle) - H/2;

		TextOut(hdc, NewX, NewY, szText, strlen(szText));
	}
}

void RomanNumerals(HDC hdc, int R, int H)
{
	for (int i = 1, a = 30; i <= 12; i++, a += 30)
	{
		char szText[5];

		double radAngle = a * M_PI / 180;
		int NewX = XMAX/2 + R*sin(radAngle) - 5,
			NewY = YMAX/2 - R*cos(radAngle) - H/2;

		switch(i)
		{
		case 1:  strcpy(szText, "I");    break;
		case 2:  strcpy(szText, "II");   break;
		case 3:  strcpy(szText, "III");  break;
		case 4:  strcpy(szText, "IV");   break;
		case 5:  strcpy(szText, "V");    break;
		case 6:  strcpy(szText, "VI");   break;
		case 7:  strcpy(szText, "VII");  break;
		case 8:  strcpy(szText, "VIII"); break;
		case 9:  strcpy(szText, "IX");   break;
		case 10: strcpy(szText, "X");    break;
		case 11: strcpy(szText, "XI");   break;
		case 12: strcpy(szText, "XII");  break;
		}

		TextOut(hdc, NewX, NewY, szText, strlen(szText));
	}
}

void ClockDial(HDC hdc)
{
	const int R = 220;

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	switch(swBrushColor)
	{
	case IDM_WHITE:           SelectBrush(hdc, hWhiteBrush);           break;
	case IDM_CHARTREUSE:      SelectBrush(hdc, hChartreuseBrush);      break;
	case IDM_HELIOTROPE:      SelectBrush(hdc, hHeliotropeBrush);      break;
	case IDM_LIME:            SelectBrush(hdc, hLimeBrush);            break;
	case IDM_MALACHITE:       SelectBrush(hdc, hMalachiteBrush);       break;
	case IDM_MINTGREEN:       SelectBrush(hdc, hMintGreenBrush);       break;
	case IDM_PANG:            SelectBrush(hdc, hPangBrush);            break;
	case IDM_PERIWINKLE:      SelectBrush(hdc, hPeriwinkleBrush);      break;
	case IDM_SCHOOLBUSYELLOW: SelectBrush(hdc, hSchoolBusYellowBrush); break;
	case IDM_ZINNWALDITE:     SelectBrush(hdc, hZinnwalditeBrush);     break;
	}

	Ellipse(hdc, 50, 50, XMAX-50, YMAX-50);

	SetBkMode(hdc, TRANSPARENT);

	switch(swNumerals)
	{
	case IDM_ARABIC: ArabicNumerals(hdc, R, tm.tmHeight); break;
	case IDM_ROMAN:  RomanNumerals( hdc, R, tm.tmHeight); break;
	}
}

inline int HoursToDegrees(int Hours)
{
	const int HoursPerDay = 12;
	return 360 / HoursPerDay * Hours;
}

inline int MinOrSecToDegrees(int Minutes)
{
	const int MinsPerHour = 60;
	return 360 / MinsPerHour * Minutes;
}

void HourHand(HDC hdc, int degAngle, int Length, HPEN hPen)
{
	double radAngle = degAngle * M_PI / 180;

	int NewX = XMAX/2 + Length*sin(radAngle),
		NewY = YMAX/2 - Length*cos(radAngle);

	SelectPen(hdc, hPen);

	MoveToEx(hdc, XMAX/2, YMAX/2, 0);
	LineTo(hdc, NewX, NewY);
}

void PrintText(HDC hdc)
{
	char szText[] = "Вербин Илья K8-171";

	switch(swFontName)
	{
	case IDM_FONTARIAL:
		switch(swFontSize)
		{
		case 16: SelectFont(hdc, hFont16A); break;
		case 20: SelectFont(hdc, hFont20A); break;
		case 24: SelectFont(hdc, hFont24A); break;
		}
		break;

	case IDM_FONTCOURIER:
		switch(swFontSize)
		{
		case 16: SelectFont(hdc, hFont16C); break;
		case 20: SelectFont(hdc, hFont20C); break;
		case 24: SelectFont(hdc, hFont24C); break;
		}
		break;

	case IDM_FONTTIMES:
		switch(swFontSize)
		{
		case 16: SelectFont(hdc, hFont16T); break;
		case 20: SelectFont(hdc, hFont20T); break;
		case 24: SelectFont(hdc, hFont24T); break;
		}
	}

	TextOut(hdc, 20, YMAX-40, szText, strlen(szText));
}

void OnPaint(HWND hwnd)
{
	SYSTEMTIME lt;
	GetLocalTime(&lt);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	ClockDial(hdc);

	HourHand(hdc, HoursToDegrees(lt.wHour),      120, hHourPen);
	HourHand(hdc, MinOrSecToDegrees(lt.wMinute), 170, hMinPen);
	HourHand(hdc, MinOrSecToDegrees(lt.wSecond), 200, hSecPen);

	PrintText(hdc);

	EndPaint(hwnd, &ps);
}

void OnDestroy(HWND)
{
	PostQuitMessage(0);
}
