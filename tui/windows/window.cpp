#include <cstring>
#include "screen.h"
#include "window.h"

void Window::Draw()
{
	for (short i = x + 1; i <= x + w; i++)
		for (short j = y + 1; j <= y + h; j++)
			Screen::Set(i, j, ' ');

	if (active) DrawActiveBorder();
	else DrawPassiveBorder();

	need_repaint = false;
}

void Window::DrawActiveBorder()
{
	int new_x = x + dx,
		new_y = y + dy;

	for (short i = 1; i <= w; i++)
	{
		Screen::Set(new_x + i, new_y, 0xCD);
		Screen::Set(new_x + i, new_y + h + 1, 0xCD);
	}

	for (i = 1; i <= h; i++)
	{
		Screen::Set(new_x, new_y + i, 0xBA);
		Screen::Set(new_x + w + 1, new_y + i, 0xBA);
	}

	Screen::Set(new_x, new_y, 0xC9);
	Screen::Set(new_x + w + 1, new_y, 0xBB);
	Screen::Set(new_x, new_y + h + 1, 0xC8);
	Screen::Set(new_x + w + 1, new_y + h + 1, 0xBC);

	Screen::PrintText(new_x + (w - strlen(caption)) / 2 + 1, new_y, caption);
}

void Window::DrawPassiveBorder()
{
	for (short i = 1; i <= w; i++)
	{
		Screen::Set(x + i, y, 0xC4);
		Screen::Set(x + i, y + h + 1, 0xC4);
	}

	for (i = 1; i <= h; i++)
	{
		Screen::Set(x, y + i, 0xB3);
		Screen::Set(x + w + 1, y + i, 0xB3);
	}

	Screen::Set(x, y, 0xDA);
	Screen::Set(x + w + 1, y, 0xBF);
	Screen::Set(x, y + h + 1, 0xC0);
	Screen::Set(x + w + 1, y + h + 1, 0xD9);

	Screen::PrintText(x + (w - strlen(caption)) / 2 + 1, y, caption);
}

Window::Window(short new_x, short new_y, short new_w, short new_h,
			   const char *new_caption, bool new_active)
{
	x = new_x;
	y = new_y;
	w = new_w;
	h = new_h;

	dx = dy = 0;

	strncpy(caption, new_caption, MAX_CAPTION);

	active = new_active;
	moving = false;
	need_repaint = true;
}

void Window::KeyPressed(int c1, int c2)
{
	if ((!c1) && (0x62 == c2))						// Ctrl + F5
		moving = true;

	else if ((-1 == c1) && (0x0D == c2))			// Enter
	{
		moving = false;
		x += dx;
		y += dy;
		dx = dy = 0;
		need_repaint = true;
	}

	else if ((0xE0 == c1) && moving)
		switch (c2)
		{
			case 0x48:								// Up
				if (y + dy > 0) dy--;
				need_repaint = true;
				break;

			case 0x50:								// Down
				if (y + h + dy + 2 < Screen::height) dy++;
				need_repaint = true;
				break;

			case 0x4B:								// Left
				if (x + dx > 0) dx--;
				need_repaint = true;
				break;

			case 0x4D:								// Right
				if (x + w + dx + 2 < Screen::width) dx++;
				need_repaint = true;
				break;
		}
}
