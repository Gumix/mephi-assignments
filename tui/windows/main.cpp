#include <iostream>
using std::cout;
#include <conio.h>
#include "screen.h"
#include "window.h"
#include "editor.h"

int main()
{
	const max_windows = 20;
	Window *w[max_windows];

	w[0] = new Editor(1, 1, 26, 1, "Editor", true);
	char active = 0, windows = 1;
	bool need_repaint = false;

	while (1)
	{
		Screen::HideCursor();
		if (w[active]->NeedRepaint() || need_repaint)
		{
			Screen::ClrScr();
			for (int i = 0; i < windows; i++)
				if (i != active) w[i]->Draw();
			w[active]->Draw();
		}
		Screen::PutCursor();
		need_repaint = false;

		int c1 = _getch();
		if (0x1B == c1) break;			// ESC

		else if ((!c1) || (0xE0 == c1))
		{
			int c2 = _getch();
			switch (c2)
			{
				case 0x3B:				// F1
					w[active]->Inactive();
					w[windows] = new Editor(1, 1 + 4 * windows, 26, 1, "Editor", true);
					windows++;
					active++;
					break;

				case 0x3C:				// F2
					w[active]->Inactive();
					w[windows] = new Window(50, 1 + 5 * windows, 10, 2, "Window", true);
					windows++;
					active++;
					need_repaint = true;
					break;

				case 0x3D:				// F3
					delete w[windows - 1];
					windows--;
					if (active > 0)
					{
						active--;
						w[active]->Active();
					}
					break;

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

		if (windows <= 0) break;
	}

	Screen::ClrScr();

	for (int i = 0; i < windows; i++)
	{
		w[i]->GetText();
		delete w[i];
	}

	return 0;
}
