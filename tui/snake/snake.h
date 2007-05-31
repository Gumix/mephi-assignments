#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "rect.h"

// Класс "змейка"

class Snake
{
	enum { MAX = 100 };

	short size, head;
	char dx, dy, tail_dx, tail_dy;
	bool run;
	Rect *rects[MAX];
	int fill;

	void Run() { run = true; }
	void ChangeDirection();
	void MoveRect(short &, short &, short);
	void Eat(char);
	void operator+=(char);

public:
	Snake(short, short, short, int);
	~Snake();

	void GoToUp();
	void GoToLeft();
	void GoToRight();
	void GoToDown();
	bool Go();
};

#endif
