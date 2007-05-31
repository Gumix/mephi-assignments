#ifndef _MAIN_H_
#define _MAIN_H_

#include "snake.h"

// Головной класс

class Main
{
	static enum { MAX_PLAYERS = 2 };

	Snake *snake[MAX_PLAYERS];
	short num_players;
	short sleep_time;

public:
	Main();
	~Main();
	void Run();
};

#endif
