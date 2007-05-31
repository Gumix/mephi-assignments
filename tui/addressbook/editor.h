#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "window.h"

class Editor : public Window
{
	enum { MAX_TEXT = 255 };
	char text[MAX_TEXT];
	short cursor, view, length;
	bool need_update;

	void AddChar(int);
	void DeleteCharLeft();
	void DeleteCharRight();

public:
	Editor(short, short, short, short, const string, bool = false, const char * = NULL);

	void Draw();
	void KeyPressed(int, int);
	void Active();
	void Inactive() { Window::Inactive(); view = 0; }

	void SetText(const char *);
	char *GetText() { need_update = false; return text; }

	bool NeedUpdate() const { return need_update; }
};

#endif