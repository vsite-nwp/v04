#include "nwpwin.h"

class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		cur_pos = p;
		if (!ship)
			ship.Create(*this, STYLE_1, "X", 0, p.x, p.y, size, size);
		else
		{
			::SetWindowPos(ship, 0, p.x, p.y, 0, 0, STYLE);
		}
	}
	void OnKeyUp(int vk) {
		if (ship) {
			::SetWindowLong(ship, GWL_STYLE, STYLE_1|WS_BORDER);
			::SetWindowPos(ship, 0, cur_pos.x, cur_pos.y, 0, 0, STYLE);
		}
	}
	void OnKeyDown(int vk) {
		bool ctrl = GetAsyncKeyState(VK_CONTROL);
		RECT rc; ::GetClientRect(*this, &rc);
		int speed=ctrl ? 10 : 2;
		switch (vk)
		{
		case VK_UP:
			cur_pos.y = max(cur_pos.y - speed, rc.top);
			break;
		case VK_DOWN:
			cur_pos.y = min(cur_pos.y + speed, rc.bottom - size);
			break;
		case VK_LEFT:
			cur_pos.x = max(cur_pos.x - speed, rc.left);
			break;
		case VK_RIGHT:
			cur_pos.x = min(cur_pos.x + speed, rc.right - size);
			break;
		default: return;
		}
		::SetWindowLong(ship, GWL_STYLE, STYLE_1 |WS_BORDER );
		::SetWindowPos(ship, 0, cur_pos.x, cur_pos.y, 0, 0, STYLE);
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT cur_pos;
	const long STYLE_1 = WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER;
	const long STYLE = SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;
	const int size = 30;
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
