#include "rect.h"
#include "coord.h"

bool Rect::MoveTo(short new_x, short new_y, int fill)
{
	if (Coord::IsSetSnake(new_x, new_y))
		return false;

	Screen::Delete(x, y);

	x = new_x;
	y = new_y;

	Screen::Set(x, y, fill);

	return true;
}
