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
	need_update = true;
}

void Editor::DeleteCharLeft()
{
	if (cursor <= 0) return;

	for (int i = cursor - 1; i < length; i++)
		text[i] = text[i + 1];

	length--;
	cursor--;
	if ((view > 0) && (cursor <= view)) view--;
	need_update = true;
}

void Editor::DeleteCharRight()
{
	if (cursor >= length) return;

	for (int i = cursor; i < length; i++)
		text[i] = text[i + 1];

	length--;
	need_update = true;
}

Editor::Editor(short new_x, short new_y, short new_w, short new_h,
			   const string new_caption, bool new_active, const char *new_text)
	: Window(new_x, new_y, new_w, new_h, new_caption, new_active)
{
	if (active) Screen::MoveCursor(x + 1, y + 1);

	SetText(new_text);
	view = 0;
	need_update = false;
}

void Editor::Draw()
{
	Window::DrawBody();
	Screen::PrintText(x + 1, y + 1, text + view, w);
	if (active) DrawActiveBorder();
	else DrawPassiveBorder();

	if (active && !moving)
	{
		if (view > 0) Screen::PrintLeftArrow(x, y + 1);
		if (length > w + view) Screen::PrintRightArrow(x + w + 1, y + 1);
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

	else if (-1 == c1)
	{
		if ((c2 >= 32) && (c2 <= 126))
		{
			AddChar(c2);
			need_repaint = true;
		}
		else if (8 == c2)							// Backspace
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
	if (cursor > w) cursor = w - 1;
	Screen::MoveCursor(x + 1 + cursor - view, y + 1);
}

void Editor::SetText(const char *new_text)
{
	if (new_text)
	{
		strncpy(text, new_text, MAX_TEXT);
		length = cursor = strlen(text);
	}
	else
		length = cursor = text[0] = 0;
}
