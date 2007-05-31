#include <cstring>
#include "screen.h"
#include "editor.h"

void Editor::AddChar(int c)
{
	if (length + 1 >= MAX_TEXT) return;

	for (int i = length + 1; i > cursor; i--)
		text[i] = text[i - 1];

	text[cursor] = c;
	length++;
	cursor++;
	if (length >= w) view++;
}

void Editor::DeleteCharLeft()
{
	if (cursor <= 0) return;

	for (int i = cursor - 1; i < length; i++)
		text[i] = text[i + 1];

	length--;
	cursor--;
	if ((view > 0) && (cursor <= view)) view--;
}

void Editor::DeleteCharRight()
{
	if (cursor >= length) return;

	for (int i = cursor; i < length; i++)
		text[i] = text[i + 1];

	length--;
}

Editor::Editor(short new_x, short new_y, short new_w, short new_h, const char *new_caption, bool new_active)
	: Window(new_x, new_y, new_w, new_h, new_caption, new_active)
{
	if (active) Screen::MoveCursor(x + 1, y + 1);

	length = text[0] = cursor = view = 0;
}

void Editor::Draw()
{
	Window::Draw();
	Screen::PrintText(x + 1, y + 1, text + view, w);

	if (active && !moving)
	{
		if (view > 0) Screen::PrintLeftArrow(x, y + 1);
		else Screen::DeleteArrow(x, y + 1);

		if (length > w + view) Screen::PrintRightArrow(x + w + 1, y + 1);
		else Screen::DeleteArrow(x + w + 1, y + 1);

		Screen::ShowCursor();
	}
}

void Editor::KeyPressed(int c1, int c2)
{
	Window::KeyPressed(c1, c2);
	if (moving)
	{
		Screen::HideCursor();
		return;
	}

	if (0xE0 == c1)
		switch (c2)
		{
			case 0x48:								// Up
				view = 0;
				cursor = 0;
				need_repaint = true;
				break;

			case 0x50:								// Down
				if (length >= w) view = length - w + 1;
				cursor = length;
				need_repaint = true;
				break;

			case 0x4B:								// Left
				if ((view > 0) && (cursor <= view)) view--;
				cursor--;
				if (cursor < 0) cursor = 0;
				need_repaint = true;
				break;

			case 0x4D:								// Right
				if (cursor >= view + w - 1) view++;
				cursor++;
				if (cursor > length) cursor = length;
				need_repaint = true;
				break;

			case 0x53:								// Delete
				DeleteCharRight();
				need_repaint = true;
				break;
		}

	else if (c1 == -1)
	{
		if ((c2 >= 32) && (c2 <= 126))
		{
			AddChar(c2);
			need_repaint = true;
		}

		else if (c2 == 8)							// Backspace
		{
			DeleteCharLeft();
			need_repaint = true;
		}
	}

	Screen::MoveCursor(x + 1 + cursor - view, y + 1);
	Screen::ShowCursor();
}

void Editor::Active()
{
	Window::Active();
	Screen::MoveCursor(x + 1 + cursor, y + 1);
}