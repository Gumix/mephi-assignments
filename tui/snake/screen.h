#ifndef _SCREEN_H_
#define _SCREEN_H_

// Класс, обеспечивающий вывод на монитор

class Screen
{
	static short num_players;

	static void ClrScr();
	static void HideCursor();
	static void DrawBorder();

public:
	static void GoToXY(short, short);
	static void Init(short);
	static void Set(short, short, int);
	static void Delete(short, short);
	static void UpdateCounter(short, int);
	static void PrintNum(short, short, short);
};

#endif
