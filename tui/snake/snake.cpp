#include "snake.h"
#include "coord.h"
#include "screen.h"

void Snake::ChangeDirection()
{
	head = !head ? size-1 : 0;

	tail_dx ^= dx ^= tail_dx ^= dx;
	tail_dy ^= dy ^= tail_dy ^= dy;
}

void Snake::MoveRect(short &x1, short &y1, short i)
{
	short x2 = rects[i]->GetX(),
		  y2 = rects[i]->GetY();

	rects[i]->MoveTo(x1, y1, fill);

	tail_dx = x2 - x1;
	tail_dy = y2 - y1;

	x1 = x2;
	y1 = y2;
}

void Snake::Eat(char num)
{
	*this += num;

	Screen::UpdateCounter(size, fill);

	Coord::GenerateNum();
}

void Snake::operator+=(char num)
{
	if (!head)
	{
		short tail_x = rects[size-1]->GetX(),
			  tail_y = rects[size-1]->GetY();

		for (char i = 0; i < num; i++)
			rects[size+i] = new Rect(tail_x, tail_y, fill);

		size += num;
	}
	else
	{
		short tail_x = rects[0]->GetX(),
			  tail_y = rects[0]->GetY();

		for (char i = size-1; 0 <= i; i--)
			rects[i+num] = rects[i];

		for (i = 0; i < num; i++)
			rects[i] = new Rect(tail_x, tail_y, fill);

		size += num;
		head = size-1;
	}
}

Snake::Snake(short new_size, short x, short y, int new_fill)
	: size(new_size), head(0), dx(1), dy(0), tail_dx(-1), tail_dy(0),
	  run(false), fill(new_fill)
{
	for (short i = 0; i < size; i++)
		rects[i] = new Rect(x - i, y, fill);

	Screen::UpdateCounter(size, fill);
}

Snake::~Snake()
{
	for (short i = 0; i < size; i++)
		delete rects[i];
}

void Snake::GoToUp()
{
	Run();

	if (1 == dy)	// if down
		ChangeDirection();
	else
		dx =  0,
		dy = -1;
}

void Snake::GoToLeft()
{
	Run();

	if (1 == dx)	// if right
		ChangeDirection();
	else
		dx = -1,
		dy =  0;
}

void Snake::GoToRight()
{
	Run();

	if (-1 == dx)	// if left
		ChangeDirection();
	else
		dx = 1,
		dy = 0;
}

void Snake::GoToDown()
{
	Run();

	if (-1 == dy)	// if up
		ChangeDirection();
	else
		dx = 0,
		dy = 1;
}

bool Snake::Go()
{
	if (!run)
		return true;

	tail_dx = -dx;
	tail_dy = -dy;

	short head_x = rects[head]->GetX(),
		  head_y = rects[head]->GetY();

	char num = Coord::GetNum(head_x + dx, head_y + dy);

	if (!rects[head]->MoveTo(head_x + dx, head_y + dy, fill))
		return false;

	if (!head)
		for (short i = 1; i < size; i++)
			MoveRect(head_x, head_y, i);
	else
		for (short i = size - 2; i >= 0; i--)
			MoveRect(head_x, head_y, i);

	if (-1 < num)
		Eat(num);

	return true;
}
