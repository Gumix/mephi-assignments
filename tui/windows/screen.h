#ifndef _SCREEN_H_
#define _SCREEN_H_

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
	static void PutCursor();
	static void MoveCursor(short, short);

	static void Set(short, short, int);
	static void PrintText(short, short, const char *);
	static void PrintText(short, short, const char *, short);

	static void PrintLeftArrow(short, short);
	static void PrintRightArrow(short, short);
	static void DeleteArrow(short, short);
};

#endif
