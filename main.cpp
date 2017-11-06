#include "nwpwin.h"
using namespace std;

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
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		}
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		cur_pos = p;
	}
	void OnKeyUp(int vk) {

		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos(st, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnKeyDown(int vk) {
		RECT r;
		GetClientRect(*this, &r);
		int brzina;
		GetKeyState(VK_CONTROL) == 0 ? brzina = 10 : brzina = 2;
		switch (vk) {
		case VK_UP:
			cur_pos.y = max(cur_pos.y - brzina, 0);
			/*cur_pos.y = cur_pos.y - brzina;
			if (cur_pos.y < r.top) { cur_pos.y = 0; }*/
			break;
		case VK_DOWN:
			cur_pos.y = min(cur_pos.y + brzina, r.bottom - 20);
			/*cur_pos.y = cur_pos.y + brzina;
			if (cur_pos.y > r.bottom) { cur_pos.y = r.bottom - 20; }*/
			break;
		case VK_LEFT:
			cur_pos.x = max(cur_pos.x - brzina, 0);
			/*cur_pos.x = cur_pos.x - brzina;
			if (cur_pos.x < r.left) { cur_pos.x = 0; }*/
			break;
		case VK_RIGHT:
			cur_pos.x = min(cur_pos.x + brzina, r.right - 20);
			/*cur_pos.x = cur_pos.x + brzina;
			if (cur_pos.x > r.right) { cur_pos.x = r.right - 20; }*/
			break;

		}
		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER| SS_CENTER);
		SetWindowPos(st, 0, cur_pos.x, cur_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnDestroy() {
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
