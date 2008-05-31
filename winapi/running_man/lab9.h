#pragma once

#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND, CREATESTRUCT FAR *);
void OnPaint(HWND);
void OnGetMinMaxInfo(HWND, LPMINMAXINFO);
void OnDestroy(HWND);

void CALLBACK OnTimer(HWND hwnd, UINT, UINT, DWORD);

void Bezier3(int *, int *, int *, int *, double);