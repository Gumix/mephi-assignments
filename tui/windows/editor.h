#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <iostream>
using std::cout;
#include "window.h"

const MAX_TEXT = 255;

class Editor : public Window
{
	char text[MAX_TEXT];
	short cursor, view, length;

	void AddChar(int);
	void DeleteCharLeft();
	void DeleteCharRight();

public:
	Editor(short, short, short, short, const char *, bool = false);

	void Draw();
	void KeyPressed(int, int);
	void Active();

	void GetText() { cout << text << '\n'; }
};

#endif