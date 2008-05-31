#include "stdafx.h"
#include "proc1.h"

int n = 5;
int l = 100;
int color = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	DialogBox(hInst, (LPCWSTR)IDD_DIALOGBOX, NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, DlgOnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, DlgOnCommand);
	default:
		return FALSE;
	}
}

BOOL DlgOnInitDialog(HWND hwnd, HWND, LPARAM)
{
	WCHAR szText[5];

	_itow_s(n, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), (LPCWSTR)szText);

	_itow_s(l, szText, 10);
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT2), (LPCWSTR)szText);

	return TRUE;
}

void DlgOnCommand(HWND hwnd, int id, HWND, UINT CodeNotify)
{
	int nData[3];
	HWND hwndRcv;
	WCHAR szText[5];
	COPYDATASTRUCT cds;

	switch (id)
	{
	case ID_BUTTON:
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), szText, 4);
		n = _wtoi(szText);
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT2), szText, 4);
		l = _wtoi(szText);

		hwndRcv = FindWindow(NULL, L"Процесс 2");
		if (!hwndRcv)
			MessageBox(NULL, L"Процесс 2 не запущен!", L"Ошибка!", MB_OK);
		else
		{
			nData[0] = n;
			nData[1] = l;
			nData[2] = color;

			cds.dwData = 0;
			cds.cbData = sizeof(nData);
			cds.lpData = (PVOID)nData;
			SendMessage(hwndRcv, WM_COPYDATA, NULL, (LPARAM)&cds);
		}
		break;

	case ID_COLOR1:
		color = 0;
		break;
	case ID_COLOR2:
		color = RGB(255, 0, 0);
		break;
	case ID_COLOR3:
		color = RGB(0, 255, 0);
		break;
	case ID_COLOR4:
		color = RGB(0, 0, 255);
		break;

	case IDCANCEL:
		EndDialog(hwnd, 0);
	}
}
