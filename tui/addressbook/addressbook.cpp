#include "addressbook.h"

AddressBook::AddressBook()
{
	w[LIST] = new List(5, 3, 26, 11, "Names", true);
	w[MASK] = new Editor(5, 17, 26, 1, "Mask", false, "*");
	w[NAME] = new Editor(40, 3, 26, 1, "Name");
	w[NUMB] = new Editor(40, 8, 26, 1, "Telephone number");
	w[NOTE] = new Editor(40, 13, 26, 1, "Note");

	active = LIST;
	need_save = false;
}

int AddressBook::ReadFromFile(const char *new_filename)
{
	strncpy(filename, new_filename, max_filename);
	ifstream input(filename);
	if (!input) return 1;

	const max = 255;
	char line[max];
	string str;
	Person item;

	while (!input.eof())
	{
		input.getline(line, max);
		str = line;
		int first  = str.find('&');
		int second = str.find('&', first + 1);

		item.name  = str.substr(0, first);
		item.phone = str.substr(first + 1, second - first - 1);
		item.note  = str.substr(second + 1, str.length() - second - 1);
		if (item.name != "") ((List *) w[LIST])->AddItem(item);
	}

	return 0;
}

void AddressBook::Run()
{
	((List *) w[LIST])->SetFilter(((Editor *) w[MASK])->GetText());

	while (1)
	{
		Screen::HideCursor();

		if (w[LIST]->NeedUpdate())
		{
			Person p;
			if (need_save)
			{
				p.name  = ((Editor *) w[NAME])->GetText();
				p.phone = ((Editor *) w[NUMB])->GetText();
				p.note  = ((Editor *) w[NOTE])->GetText();
				((List *) w[LIST])->UpdatePerson(p);
				((List *) w[LIST])->SaveToFile(filename);
				need_save = false;
			}

			p = ((List *) w[LIST])->GetPerson();
			((Editor *) w[NAME])->SetText(p.name.c_str());
			((Editor *) w[NUMB])->SetText(p.phone.c_str());
			((Editor *) w[NOTE])->SetText(p.note.c_str());
		}

		if (((List *) w[LIST])->NeedSave()) ((List *) w[LIST])->SaveToFile(filename);
		need_save |= w[NAME]->NeedUpdate() | w[NUMB]->NeedUpdate() | w[NOTE]->NeedUpdate();
		if (w[MASK]->NeedUpdate())
		{
				((Editor *) w[NAME])->SetText("");
				((Editor *) w[NUMB])->SetText("");
				((Editor *) w[NOTE])->SetText("");
				((List *) w[LIST])->SetFilter(((Editor *) w[MASK])->GetText());
		}

		if (w[active]->NeedRepaint())
		{
			Screen::ClrScr();
			for (int i = 0; i < windows; i++) if (i != active) w[i]->Draw();
			w[active]->Draw();
		}
		Screen::PutCursor();

		int c1 = _getch();
		if (0x1B == c1) break;			// ESC

		else if (!c1 || (0xE0 == c1))
		{
			int c2 = _getch();
			switch (c2)
			{
				case 0x40:				// F6
					w[active]->Inactive();
					active = (active + 1) % windows;
					w[active]->Active();
					break;

				default:
					w[active]->KeyPressed(c1, c2);
					break;
			}
		}
		else w[active]->KeyPressed(-1, c1);
	}

	Screen::ClrScr();
}
