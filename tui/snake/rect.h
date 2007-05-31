#ifndef _RECT_H_
#define _RECT_H_

#include "screen.h"

// Класс "прямоугольник"

class Rect
{
	short x, y;

public:
	Rect(short new_x, short new_y, int fill) : x(new_x), y(new_y) { Screen::Set(x, y, fill); }

	short GetX() const { return x; }
	short GetY() const { return y; }

	bool MoveTo(short, short, int);
};

#endif
