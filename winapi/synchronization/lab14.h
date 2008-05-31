#pragma once

#include "resource.h"

#define RAND(n)	(int(rand()/(RAND_MAX+1.0)*(n))+1)

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void DlgOnCommand(HWND, int, HWND, UINT);

DWORD WINAPI CarsGeneratorThread(LPVOID);
DWORD WINAPI QueueCounterThread(LPVOID);
DWORD WINAPI Car80Thread(LPVOID);
DWORD WINAPI Car92Thread(LPVOID);
DWORD WINAPI Car95Thread(LPVOID);
DWORD WINAPI Car98Thread(LPVOID);