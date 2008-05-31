#include "stdafx.h"
#include "lab14.h"

int Pump80Count = 1;
int Pump92Count = 3;
int Pump95Count = 3;
int Pump98Count = 1;

HANDLE hSem80, hSem92, hSem95, hSem98;
int Car80Count, Car92Count, Car95Count, Car98Count;
int Pump80MaxCar, Pump92MaxCar, Pump95MaxCar, Pump98MaxCar;
bool Go;
int TimeScale = 10;
int oldTimeScale;
int StartTime;
int QueueCount;
int TotalQueueCars;
long TotalQueueTime;
bool bTimeStop;
bool bOpt;
int nTimeStop;
HWND hMainWnd;

int oldPump80Count, oldPump92Count, oldPump95Count, oldPump98Count;

int TotalQueueCars80, TotalQueueCars92, TotalQueueCars95, TotalQueueCars98;
int TotalQueueTime80, TotalQueueTime92, TotalQueueTime95, TotalQueueTime98;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	srand(time(NULL));
	DialogBox(hInst, (LPCWSTR)IDD_DIALOG, NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_COMMAND, DlgOnCommand);
	default:
		return FALSE;
	}
}

void DlgOnCommand(HWND hwnd, int id, HWND, UINT CodeNotify)
{
	switch (id)
	{
	case ID_SCALE10:
		TimeScale = 10;
		break;

	case ID_SCALE100:
		TimeScale = 100;
		break;

	case IDC_START:
		hMainWnd = hwnd;

		EnableWindow( GetDlgItem(hwnd, IDC_START), FALSE );
		EnableWindow( GetDlgItem(hwnd, IDC_DAY), FALSE );
		EnableWindow( GetDlgItem(hwnd, IDC_OPTIMAL), FALSE );
		EnableWindow( GetDlgItem(hwnd, IDC_STOP), TRUE );
		SendDlgItemMessage(hwnd, IDC_LIST80, LB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hwnd, IDC_LIST92, LB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hwnd, IDC_LIST95, LB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hwnd, IDC_LIST98, LB_RESETCONTENT, 0, 0);
		SetWindowText( GetDlgItem(hwnd, IDC_EDIT_QUEUE), (LPCWSTR)L"Очереди нет" );
		WCHAR szText[30];
		wsprintf(szText, L"Число колонок: %d", Pump80Count);
		SendDlgItemMessage(hwnd, IDC_LIST80, LB_ADDSTRING, 0, (LPARAM)szText);
		wsprintf(szText, L"Число колонок: %d", Pump92Count);
		SendDlgItemMessage(hwnd, IDC_LIST92, LB_ADDSTRING, 0, (LPARAM)szText);
		wsprintf(szText, L"Число колонок: %d", Pump95Count);
		SendDlgItemMessage(hwnd, IDC_LIST95, LB_ADDSTRING, 0, (LPARAM)szText);
		wsprintf(szText, L"Число колонок: %d", Pump98Count);
		SendDlgItemMessage(hwnd, IDC_LIST98, LB_ADDSTRING, 0, (LPARAM)szText);

		hSem80 = CreateSemaphore(NULL, Pump80Count, Pump80Count, NULL);
		hSem92 = CreateSemaphore(NULL, Pump92Count, Pump92Count, NULL);
		hSem95 = CreateSemaphore(NULL, Pump95Count, Pump95Count, NULL);
		hSem98 = CreateSemaphore(NULL, Pump98Count, Pump98Count, NULL);

		Car80Count = 0;
		Car92Count = 0;
		Car95Count = 0;
		Car98Count = 0;

		QueueCount = 0;
		TotalQueueCars = 0;
		TotalQueueTime = 0;
		TotalQueueCars80 = 0;
		TotalQueueTime80 = 0;
		TotalQueueCars92 = 0;
		TotalQueueTime92 = 0;
		TotalQueueCars95 = 0;
		TotalQueueTime95 = 0;
		TotalQueueCars98 = 0;
		TotalQueueTime98 = 0;

		Pump80MaxCar = Pump80Count;
		Pump92MaxCar = Pump92Count;
		Pump95MaxCar = Pump95Count;
		Pump98MaxCar = Pump98Count;

		StartTime = GetTickCount();

		Go = true;
		DWORD id;
		CreateThread(NULL, 0, CarsGeneratorThread, 0, 0, &id);
		CreateThread(NULL, 0, QueueCounterThread, 0, 0, &id);
		break;

	case IDC_DAY:
		bTimeStop = true;
		nTimeStop = 24*60*60;
		TimeScale = 1000;
		SendMessage(hwnd, WM_COMMAND, IDC_START, 0);
		break;

	case IDC_OPTIMAL:
		oldPump80Count = Pump80Count;
		oldPump92Count = Pump92Count;
		oldPump95Count = Pump95Count;
		oldPump98Count = Pump98Count;

		Pump80Count = 1;
		Pump92Count = 1;
		Pump95Count = 1;
		Pump98Count = 1;

		bTimeStop = true;
		bOpt = true;
		nTimeStop = 5000;
		TimeScale = 1000;

		SendMessage(hwnd, WM_COMMAND, IDC_START, 0);
		break;

	case IDC_STOP:
		Go = false;
		break;

	case IDCANCEL:
		EndDialog(hwnd, 0);
	}
}

void WaitForNextCar()
{
	int SleepTime = RAND(4) * 30;	// от 30 до 120 с шагом 30

	Sleep(SleepTime*1000/TimeScale);
}

void CarFilling()
{
	int FillingTime = RAND(6) + 4;	// от 5 до 10 с шагом 1

	Sleep(FillingTime*60*1000/TimeScale);
}

int GenCarType()
{
	int r = RAND(12);	// от 1 до 12 с шагом 1

	switch (r)
	{
	case 1:
	case 2:
		return 80;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return 92;
	case 8:
	case 9:
	case 10:
	case 11:
		return 95;
	case 12:
		return 98;
	}

	return 0;
}

DWORD WINAPI CarsGeneratorThread(LPVOID)
{
	while (Go)
	{
		DWORD id;
		WaitForNextCar();

		switch ( GenCarType() )
		{
		case 80:
			Car80Count++;
			CreateThread(NULL, 0, Car80Thread, (LPVOID)Car80Count, 0, &id);
			break;
		case 92:
			Car92Count++;
			CreateThread(NULL, 0, Car92Thread, (LPVOID)Car92Count, 0, &id);
			break;
		case 95:
			Car95Count++;
			CreateThread(NULL, 0, Car95Thread, (LPVOID)Car95Count, 0, &id);
			break;
		case 98:
			Car98Count++;
			CreateThread(NULL, 0, Car98Thread, (LPVOID)Car98Count, 0, &id);
			break;
		}

		if (bTimeStop && ((GetTickCount()-StartTime)/1000.0*TimeScale > nTimeStop))
		{
			Go = false;
			bOpt = false;
			bTimeStop = false;
			TimeScale = oldTimeScale;
		}
	}

	CloseHandle(hSem80);
	CloseHandle(hSem92);
	CloseHandle(hSem95);
	CloseHandle(hSem98);

	EnableWindow( GetDlgItem(hMainWnd, IDC_START), TRUE );
	EnableWindow( GetDlgItem(hMainWnd, IDC_DAY), TRUE );
	EnableWindow( GetDlgItem(hMainWnd, IDC_OPTIMAL), TRUE );
	EnableWindow( GetDlgItem(hMainWnd, IDC_STOP), FALSE );

	return 0;
}

DWORD WINAPI QueueCounterThread(LPVOID)
{
	while (Go)
	{
		WCHAR szText[100];

		if (QueueCount > 5)
		{
			int t = (GetTickCount()-StartTime)/1000.0*TimeScale;
			wsprintf(szText, L"%d с: %d машин в очереди. Среднее время нахождения машины в очереди: %d с",
					 t, QueueCount, int(double(TotalQueueTime)/TotalQueueCars+0.5));
			SetWindowText( GetDlgItem(hMainWnd, IDC_EDIT_QUEUE), (LPCWSTR)szText );
		}
		else if (TotalQueueCars)
		{
			wsprintf(szText, L"Среднее время нахождения машины в очереди: %d с",
					 int(double(TotalQueueTime)/TotalQueueCars+0.5));
			SetWindowText( GetDlgItem(hMainWnd, IDC_EDIT_QUEUE), (LPCWSTR)szText );
		}

		Sleep(10);
	}

	return 0;
}

DWORD WINAPI Car80Thread(LPVOID CarNumber)
{
	WCHAR szText[30];
	wsprintf(szText, L"Приехала машина №%d", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST80, LB_ADDSTRING, 0, (LPARAM)szText);

	DWORD t0 = GetTickCount();
	QueueCount++;
	WaitForSingleObject(hSem80, INFINITE);
	while (int(CarNumber) > Pump80MaxCar)
	{
		ReleaseSemaphore(hSem80, 1, NULL);
		Sleep(1);
		WaitForSingleObject(hSem80, INFINITE);
	}
	QueueCount--;
	DWORD t1 = GetTickCount();
	if ((t1-t0)/1000.0*TimeScale >= 1)
	{
		TotalQueueCars++;
		TotalQueueCars80++;
		TotalQueueTime += (t1-t0)/1000.0*TimeScale;
		TotalQueueTime80 += (t1-t0)/1000.0*TimeScale;
	}

	wsprintf(szText, L"Машина №%d начала заправку", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST80, LB_ADDSTRING, 0, (LPARAM)szText);

	CarFilling();

	wsprintf(szText, L"Машина №%d заправилась", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST80, LB_ADDSTRING, 0, (LPARAM)szText);

	Pump80MaxCar++;
	ReleaseSemaphore(hSem80, 1, NULL);

	return 0;
}

DWORD WINAPI Car92Thread(LPVOID CarNumber)
{
	WCHAR szText[30];
	wsprintf(szText, L"Приехала машина №%d", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST92, LB_ADDSTRING, 0, (LPARAM)szText);

	DWORD t0 = GetTickCount();
	QueueCount++;
	WaitForSingleObject(hSem92, INFINITE);
	while (int(CarNumber) > Pump92MaxCar)
	{
		ReleaseSemaphore(hSem92, 1, NULL);
		Sleep(1);
		WaitForSingleObject(hSem92, INFINITE);
	}
	QueueCount--;
	DWORD t1 = GetTickCount();
	if ((t1-t0)/1000.0*TimeScale >= 1)
	{
		TotalQueueCars++;
		TotalQueueCars92++;
		TotalQueueTime += (t1-t0)/1000.0*TimeScale;
		TotalQueueTime92 += (t1-t0)/1000.0*TimeScale;
	}

	wsprintf(szText, L"Машина №%d начала заправку", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST92, LB_ADDSTRING, 0, (LPARAM)szText);

	CarFilling();

	wsprintf(szText, L"Машина №%d заправилась", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST92, LB_ADDSTRING, 0, (LPARAM)szText);

	Pump92MaxCar++;
	ReleaseSemaphore(hSem92, 1, NULL);

	return 0;
}

DWORD WINAPI Car95Thread(LPVOID CarNumber)
{
	WCHAR szText[30];
	wsprintf(szText, L"Приехала машина №%d", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST95, LB_ADDSTRING, 0, (LPARAM)szText);

	DWORD t0 = GetTickCount();
	QueueCount++;
	WaitForSingleObject(hSem95, INFINITE);
	while (int(CarNumber) > Pump95MaxCar)
	{
		ReleaseSemaphore(hSem95, 1, NULL);
		Sleep(1);
		WaitForSingleObject(hSem95, INFINITE);
	}
	QueueCount--;
	DWORD t1 = GetTickCount();
	if ((t1-t0)/1000.0*TimeScale >= 1)
	{
		TotalQueueCars++;
		TotalQueueCars95++;
		TotalQueueTime += (t1-t0)/1000.0*TimeScale;
		TotalQueueTime95 += (t1-t0)/1000.0*TimeScale;
	}

	wsprintf(szText, L"Машина №%d начала заправку", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST95, LB_ADDSTRING, 0, (LPARAM)szText);

	CarFilling();

	wsprintf(szText, L"Машина №%d заправилась", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST95, LB_ADDSTRING, 0, (LPARAM)szText);

	Pump95MaxCar++;
	ReleaseSemaphore(hSem95, 1, NULL);

	return 0;
}

DWORD WINAPI Car98Thread(LPVOID CarNumber)
{
	WCHAR szText[30];
	wsprintf(szText, L"Приехала машина №%d", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST98, LB_ADDSTRING, 0, (LPARAM)szText);

	DWORD t0 = GetTickCount();
	QueueCount++;
	WaitForSingleObject(hSem98, INFINITE);
	while (int(CarNumber) > Pump98MaxCar)
	{
		ReleaseSemaphore(hSem98, 1, NULL);
		Sleep(1);
		WaitForSingleObject(hSem98, INFINITE);
	}
	QueueCount--;
	DWORD t1 = GetTickCount();
	if ((t1-t0)/1000.0*TimeScale >= 1)
	{
		TotalQueueCars++;
		TotalQueueCars98++;
		TotalQueueTime += (t1-t0)/1000.0*TimeScale;
		TotalQueueTime98 += (t1-t0)/1000.0*TimeScale;
	}

	wsprintf(szText, L"Машина №%d начала заправку", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST98, LB_ADDSTRING, 0, (LPARAM)szText);

	CarFilling();

	wsprintf(szText, L"Машина №%d заправилась", CarNumber);
	SendDlgItemMessage(hMainWnd, IDC_LIST98, LB_ADDSTRING, 0, (LPARAM)szText);

	Pump98MaxCar++;
	ReleaseSemaphore(hSem98, 1, NULL);

	return 0;
}
