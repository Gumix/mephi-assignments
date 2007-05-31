#ifndef _LIST_H_
#define _LIST_H_

#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "window.h"

struct Person { string name, phone, note; };

class List : public Window
{
	vector<Person> items;
	short cursor, showed_cursor, view, size;
	bool show_cursor, need_update, need_save;
	string filter;

	bool Check(const char *, const char *);
	void CalcSize();
	void FindPrev();
	void FindNext();

public:
	List(short, short, short, short, const string, bool = false);

	void AddItem(const Person item) { items.push_back(item); CalcSize(); }

	void Draw();
	void KeyPressed(int, int);
	void Active();
	void Inactive() { Window::Inactive(); show_cursor = false; }

	bool NeedUpdate() const { return need_update; }
	bool NeedSave() const { return need_save; }
	Person GetPerson() { need_update = false; return items[cursor]; }
	void UpdatePerson(const Person);
	void SaveToFile(const char *);
	void SetFilter(const string);
};

#endif