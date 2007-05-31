#ifndef _ADDRESSBOOK_H_
#define _ADDRESSBOOK_H_

#include <iostream>
#include <fstream>
using namespace std;
#include <conio.h>
#include "screen.h"
#include "window.h"
#include "editor.h"
#include "list.h"

class AddressBook
{
	enum { windows = 5, max_filename = 100 };
	enum { LIST, MASK, NAME, NUMB, NOTE };
	Window *w[windows];
	char active;
	char filename[max_filename];
	bool need_save;

public:
	AddressBook();
	~AddressBook() { for (int i = 0; i < windows; i++) delete w[i]; }

	int ReadFromFile(const char *);
	void Run();
};

#endif