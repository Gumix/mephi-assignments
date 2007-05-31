#ifndef _WINDOW_H_
#define _WINDOW_H_

const MAX_CAPTION = 20;

class Window
{
	short h, dx, dy;
	char caption[MAX_CAPTION];

	void DrawActiveBorder();
	void DrawPassiveBorder();

protected:
	short x, y, w;
	bool active, moving, need_repaint;

public:
	Window(short, short, short, short, const char *, bool = false);

	virtual void Draw();
	virtual void KeyPressed(int, int);
	virtual void Active() { active = true; need_repaint = true; }
	void Inactive() { active = false; }
	virtual void GetText() { }

	bool NeedRepaint() const { return need_repaint; }
};

#endif