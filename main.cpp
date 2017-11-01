#include "nwpwin.h"
using namespace std;

// TODO: prepare class (Static) for a ship
class Static : public Window {
	string ClassName() override { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT cur_pos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st) {
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x",0, p.x, p.y, 20, 20);
		}
		SetWindowPos(st,0,p.x,p.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		cur_pos = p;
	}
	void OnKeyUp(int vk) {

		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		RECT r;
		GetClientRect(*this, &r);
		switch (vk) {
		case VK_UP:
			cur_pos.y = cur_pos.y - 5;
			if (cur_pos.y < r.top) { cur_pos.y = 0; }
			break;
		case VK_DOWN:
			cur_pos.y = cur_pos.y + 5;
			if (cur_pos.y > r.bottom) { cur_pos.y = r.bottom-20; }
			break;
		case VK_LEFT:
			cur_pos.x = cur_pos.x - 5;
			if (cur_pos.x < r.left) { cur_pos.x = 0; }
			break;
		case VK_RIGHT:
			cur_pos.x = cur_pos.x + 5;
			if (cur_pos.x > r.right) { cur_pos.x = r.right-20; }
			break;

		}
		SetWindowPos(st, 0, cur_pos.x, cur_pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
