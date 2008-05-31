#pragma once

#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND hwnd);
BOOL OnCopyData(HWND, HWND, COPYDATASTRUCT *);
void OnDestroy(HWND);