#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <iostream>
#include <string>
using namespace std;
#include <conio.h>

class Screen
{
	static short cursor_x, cursor_y;
	static void SetColor(int);
	static void GoToXY(short, short);

public:
	static enum { width = 80, height = 25 };

	static void ClrScr();

	static void HideCursor();
	static void ShowCursor();
	static void PutCursor() { GoToXY(cursor_x, cursor_y); }
	static void MoveCursor(short new_x, short new_y) { cursor_x = new_x; cursor_y = new_y; }

	static void Set(short, short, int);
	static void PrintText(short x, short y, const string text) { GoToXY(x, y); cout << ' ' + text + ' '; }
	static void PrintText(short, short, const char *, short);
	static void PrintItem(short, short, string, short, bool);

	static void PrintLeftArrow(short x, short y)  { GoToXY(x, y); _putch(27); }
	static void PrintRightArrow(short x, short y) { GoToXY(x, y); _putch(26); }
	static void PrintUpArrow(short x, short y)    { GoToXY(x, y); _putch(24); }
	static void PrintDownArrow(short x, short y)  { GoToXY(x, y); _putch(25); }
};

#endif
