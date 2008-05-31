#pragma once

#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL DlgOnInitDialog(HWND, HWND, LPARAM);
void DlgOnCommand(HWND, int, HWND, UINT);
void DlgOnPaint(HWND);

void fArchimedeanSpiral(float, int *, int *);
void fCannabis(float, int *, int *);
void fMoon(float, int *, int *);
void fLissajousCurve(float, int *, int *);
void fEpicycloid(float, int *, int *);
