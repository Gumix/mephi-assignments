#include <windows.h>
#include "screen.h"

#define	FOREGROUND_WHITE	0x0007
#define	BACKGROUND_WHITE	0x0070

short Screen::cursor_x, Screen::cursor_y;

void Screen::SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	csbiInfo.wAttributes = color;
	SetConsoleTextAttribute(hConsole, csbiInfo.wAttributes);
}

void Screen::GoToXY(short x, short y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { x, y };
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Screen::ClrScr()
{
	COORD coordScreen = { 0, 0 };
	DWORD dwConSize, cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.wAttributes = FOREGROUND_WHITE;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize,
							   coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize,
							   coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Screen::HideCursor()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	SetConsoleMode(hInput, 0);
	GetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
}

void Screen::ShowCursor()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	SetConsoleMode(hInput, 0);
	GetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
}

void Screen::Set(short x, short y, int fill)
{
	GoToXY(x, y);
	SetColor(BACKGROUND_BLUE | FOREGROUND_WHITE);
	_putch(fill);
}

void Screen::PrintText(short x, short y, const char *text, short size)
{
	GoToXY(x, y);

	for (int i = 0; i < size; i++)
		if (!text[i]) break;
		else _putch(text[i]);
}

void Screen::PrintItem(short x, short y, string text, short size, bool selected)
{
	GoToXY(x, y);
	SetColor(selected ? BACKGROUND_WHITE | FOREGROUND_BLUE
					  : BACKGROUND_BLUE  | FOREGROUND_WHITE);

	text = text.substr(0, size);
	cout << text;
	for (int i = 0; i < size - text.length(); i++)
		cout << ' ';
}
