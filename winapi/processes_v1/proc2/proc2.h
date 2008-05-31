#pragma once

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND hwnd);
void OnDestroy(HWND);
BOOL OnCopyData(HWND, HWND, COPYDATASTRUCT *);
