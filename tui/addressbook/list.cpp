#include "screen.h"
#include "list.h"

bool List::Check(const char *text, const char *mask)
{
	while (*text)
	{
		if ((*text == *mask) || (*mask == '?'))
			text++, mask++;
		else
		{
			if (*mask != '*') return false;

			if (!*(mask + 1)) return true;

			for (const char *new_text = text + 1, *new_mask = mask + 1; *new_text; new_text++)
				if (Check(new_text, new_mask)) return true;

			return false;
		}
	}

	return !*mask;
}

void List::CalcSize()
{
	size = 0;

	for (int i = 0; i < items.size(); i++)
		if (Check(items[i].name.c_str(), filter.c_str()))
			size++;
}

void List::FindPrev()
{
	for (int i = cursor; i > 0; i--)
		if (Check(items[i - 1].name.c_str(), filter.c_str()))
		{
			cursor = i - 1;
			showed_cursor--;
			break;
		}
}

void List::FindNext()
{
	for (int i = cursor; i < items.size() - 1; i++)
		if (Check(items[i + 1].name.c_str(), filter.c_str()))
		{
			cursor = i + 1;
			showed_cursor++;
			break;
		}
}

List::List(short new_x, short new_y, short new_w, short new_h,
		   const string new_caption, bool new_active)
	: Window(new_x, new_y, new_w, new_h, new_caption, new_active)
{
	cursor = showed_cursor = view = 0;
	show_cursor = need_update = true;
	need_save = false;
}

void List::Draw()
{
	Window::DrawBody();

	for (int i = 0, j = 0; (i < items.size()) && (j < size - view) && (j < h); i++)
		if (Check(items[i + view].name.c_str(), filter.c_str()))
		{
			Screen::PrintItem(x + 1, y + 1 + j, items[i + view].name, w,
							  ((i + view == cursor) && show_cursor));
			j++;
		}

	if (active) DrawActiveBorder();
	else DrawPassiveBorder();

	if (active && !moving)
	{
		if (view > 0) Screen::PrintUpArrow(x + w + 1, y + 1);
		if (size > h + view) Screen::PrintDownArrow(x + w + 1, y + h);
	}

	need_repaint = false;
}

void List::KeyPressed(int c1, int c2)
{
	Window::KeyPressed(c1, c2);
	if (moving)
	{
		show_cursor = false;
		return;
	}

	if (0xE0 == c1)
	{
		switch (c2)
		{
			case 0x48:								// Up
				if ((view > 0) && (showed_cursor <= view)) view--;
				FindPrev();
				need_repaint = true;
				need_update = true;
				break;

			case 0x50:								// Down
				if ((view < size - h) && (showed_cursor >= view + h - 1)) view++;
				FindNext();
				need_repaint = true;
				need_update = true;
				break;

			case 0x53:								// Del
				items.erase(items.begin() + cursor);
				CalcSize();
				if (cursor < size)
				{
					if (!Check(items[cursor].name.c_str(), filter.c_str())) FindNext();
				} else FindPrev();
				need_repaint = true;
				need_update = true;
				need_save = true;
				break;
		}
	}

	else if (!c1 && (0x3E == c2))					// F4, т.к. Ins нет
	{
		Person p;
		p.name = "Noname";
		cursor++;
		showed_cursor++;
		items.insert(items.begin() + cursor, p);
		if ((view < size - h) && (showed_cursor >= view + h - 1)) view++;
		CalcSize();
		need_repaint = true;
		need_update = true;
		need_save = true;
	}

	show_cursor = true;
}

void List::Active()
{
	Window::Active();
	show_cursor = true;
	need_update = true;
}

void List::UpdatePerson(const Person p)
{
	if (Check(items[cursor].name.c_str(), filter.c_str()))
		items[cursor] = p;
}

void List::SaveToFile(const char *filename)
{
	ofstream output(filename);

	for (int i = 0; i < items.size(); i++)
		output << items[i].name << '&' << items[i].phone << '&' << items[i].note << endl;

	need_save = false;
}

void List::SetFilter(const string new_filter)
{
	filter = new_filter;
	cursor = showed_cursor = view = 0;
	if (!Check(items[cursor].name.c_str(), filter.c_str()))
		FindNext();
	CalcSize();
}
