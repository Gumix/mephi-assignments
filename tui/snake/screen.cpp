#include <conio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;
#include "screen.h"
#include "coord.h"

short Screen::num_players;

void Screen::ClrScr()
{
	COORD coordScreen = { 0, 0 };
	DWORD dwConSize, cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
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

void Screen::GoToXY(short x, short y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { x, y };
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Screen::Init(short new_num_players)
{
	num_players = new_num_players;

	ClrScr();
	HideCursor();
	DrawBorder();
}

void Screen::Set(short x, short y, int fill)
{
	Coord::Set(x, y);

	GoToXY(x, y);
	_putch(fill);
}

void Screen::Delete(short x, short y)
{
	Coord::Delete(x, y);

	GoToXY(x, y);
	_putch(' ');
}

void Screen::DrawBorder()
{
	short w = Coord::GetWidth(), h = Coord::GetHeight();

	for (short i = 1; w > i; i++)
	{
		GoToXY(i, 0); _putch(0xCD);
		GoToXY(i, h); _putch(0xCD);
	}

	for (i = 1; h > i; i++)
	{
		GoToXY(0, i); _putch(0xBA);
		GoToXY(w, i); _putch(0xBA);
	}

	GoToXY(w, 0); _putch(0xBB);
	GoToXY(0, h); _putch(0xC8);
	GoToXY(w, h); _putch(0xBC);
	GoToXY(0, 0); _putch(0xC9);
}

void Screen::UpdateCounter(short num, int fill)
{
	short w = Coord::GetWidth();

	if (1 == num_players)
	{
		GoToXY(w / 2 - 2, 0);
		cout << "[ " << setfill('0') << setw(2) << num << " ]";
	}
	else if (2 == num_players)
	{
		if (0xB1 == fill) GoToXY(3 * w / 4 - 3, 0);
		else if (0xDB == fill) GoToXY(w / 4 - 3, 0);
		cout << "[ " << char(fill) << ' ' << setfill('0') << setw(2) << num << " ]";
	}
}

void Screen::PrintNum(short x, short y, short num)
{
	GoToXY(x, y);
	cout << num;
}
