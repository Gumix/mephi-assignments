#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
using std::string;

class Window
{
	short dx, dy;
	string caption;

protected:
	short x, y, w, h;
	bool active, moving, need_repaint;

public:
	Window(short, short, short, short, const string, bool = false);

	virtual void Draw();
	void DrawBody();
	void DrawActiveBorder();
	void DrawPassiveBorder();

	virtual void KeyPressed(int, int);
	virtual void Active() { active = true; need_repaint = true; }
	virtual void Inactive() { active = false; }

	virtual bool NeedUpdate() const { return false; }
	bool NeedRepaint() const { return need_repaint; }
};

#endif