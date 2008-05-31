#pragma once

#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ParticleWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND, LPCREATESTRUCT);
void OnGetMinMaxInfo(HWND, LPMINMAXINFO);
void OnCommand(HWND, int, HWND, UINT);
void OnDestroy(HWND);

void ParticleOnPaint(HWND);

BOOL DlgOnInitDialog(HWND hwnd, HWND, LPARAM);
void DlgGetSettings();

void CALLBACK ResidueTimerProc(HWND hwnd, UINT, UINT, DWORD);