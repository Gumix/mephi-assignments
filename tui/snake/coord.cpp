#include <cstdlib>
#include "screen.h"
#include "coord.h"

signed char Coord::coord[WIDTH][HEIGHT];

bool Coord::OutOfBox(short x, short y)
{
	return (1 > x) || (WIDTH - 1 < x) || (1 > y) || (HEIGHT - 1 < y);
}

void Coord::Clear()
{
	for (char i = 0; WIDTH > i; i++)
		for (char j = 0; HEIGHT > j; j++)
			coord[i][j] = -1;
}

bool Coord::IsSetSnake(short x, short y)
{
	return (-2 == coord[x][y]) || OutOfBox(x, y);
}

bool Coord::IsSetNum(short x, short y)
{
	return (-1 != coord[x][y]) || OutOfBox(x, y);
}

void Coord::GenerateNum()
{
	short x = rand() % WIDTH,
		  y = rand() % HEIGHT;

	if (IsSetNum(x, y))
		GenerateNum();
	else
	{
		char num = rand() % (MAX_RAND + 1);
		coord[x][y] = num;
		Screen::PrintNum(x, y, num);
	}
}