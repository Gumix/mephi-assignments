#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;
#include "main.h"
#include "coord.h"
#include "screen.h"

Main::Main()
{
	srand(time(0));

	num_players = 0;
	while (num_players < 1 || num_players > MAX_PLAYERS)
	{
		cout << "Number of players (1/2): ";
		cin >> num_players;
	}

	sleep_time = 0;
	while (!sleep_time)
	{
		cout << "\n[1] Slow\n[2] Medium\n[3] Fast\n";
		cout << "Choose speed: ";
		short speed;
		cin >> speed;
		switch (speed)
		{
			case 1: sleep_time = 160; break;
			case 2: sleep_time =  80; break;
			case 3: sleep_time =  40; break;
		}
	}

	cout << "\nEnter size: ";
	short size;
	cin >> size;

	Screen::Init(num_players);
	Coord::Clear();

	snake[0] = new Snake(size, 50, 15, 0xB1);
	snake[1] = num_players == 1 ? NULL
			 : new Snake(size, 30, 10, 0xDB);

	Coord::GenerateNum();
}

Main::~Main()
{
	Screen::GoToXY(1, 1);

	for (short i = 0; i < MAX_PLAYERS; i++)
		delete snake[i];
}

void Main::Run()
{
	while (1)
	{
		if (_kbhit())
		{
			int c = _getch();

			if (0xE0 == c)
			{
				c = _getch();

				switch (c)
				{
					case 0x48: snake[0]->GoToUp();    break;
					case 0x50: snake[0]->GoToDown();  break;
					case 0x4B: snake[0]->GoToLeft();  break;
					case 0x4D: snake[0]->GoToRight(); break;
				}
			}
			else if (' ' == c)
				break;
			else if (1 < num_players)
				switch (c)
				{
					case 0x77: snake[1]->GoToUp();    break;
					case 0x73: snake[1]->GoToDown();  break;
					case 0x61: snake[1]->GoToLeft();  break;
					case 0x64: snake[1]->GoToRight(); break;
				}
		}

		for (short i = 0; i < num_players; i++)
			if (!snake[i]->Go())
				return;

		Sleep(sleep_time);
	}
}

int main()
{
	Main main;
	main.Run();

	return 0;
}
