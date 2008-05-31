#pragma once

#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL DlgOnInitDialog(HWND, HWND, LPARAM);
void DlgOnCommand(HWND, int, HWND, UINT);