#pragma once

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool OnCreate(HWND, LPCREATESTRUCT);
void OnDestroy(HWND);
void OnTimer(HWND hwnd, UINT);
void OnPaint(HWND hwnd);
void OnCommand(HWND, int, HWND, UINT);
