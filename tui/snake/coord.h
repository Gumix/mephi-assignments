#ifndef _COORD_H_
#define _COORD_H_

// Класс для хранения координат точек двухмерной плоскости экрана

class Coord
{
	static enum { WIDTH = 79, HEIGHT = 39, MAX_RAND = 4 };

	static signed char coord[WIDTH][HEIGHT];
	static bool OutOfBox(short, short);
	static bool IsSetNum(short, short);

public:
	static void Clear();

	static void Set(short x, short y) { coord[x][y] = -2; }
	static void Delete(short x, short y) { coord[x][y] = -1; }
	static bool IsSetSnake(short, short);

	static void GenerateNum();
	static char GetNum(short x, short y) { return coord[x][y]; }
	static short GetWidth() { return WIDTH; }
	static short GetHeight() { return HEIGHT; }
};

#endif
