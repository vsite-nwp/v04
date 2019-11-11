#include "nwpwin.h"
 
class Static: public Window {
public:
	std::string ClassName() override {
		return "STATIC";
	}
};

class MainWindow : public Window
{
public:
	
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) {
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", NULL, p.x, p.y, 25, 25);
			curr_pos = p;
			step(false);
		}
	}
	void OnKeyUp(int vk) {
		step(false);
	}
	void OnKeyDown(int vk) {
		int speed = 10;
		if (GetKeyState(VK_CONTROL) < 0)
			speed *= 4;
		RECT rc;
		GetClientRect(*this, &rc);

		switch (vk) {
		case (VK_LEFT):
			curr_pos.x = max(0, curr_pos.x - speed);
			break;
		case (VK_RIGHT):
			curr_pos.x = min(rc.right - 25, curr_pos.x + speed);
			break;
		case (VK_UP):
			curr_pos.y = max(0, curr_pos.y - speed);
			break;
		case(VK_DOWN):
			curr_pos.y = min(rc.bottom - 25, curr_pos.y + speed);
			break;
		default:
			return;
		}

		step(true);
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
	void step(bool border) {
		DWORD style = ::GetWindowLong(ship, GWL_STYLE);
		if (border) {
			style = (style | WS_BORDER);
		}
		else {
			style = (style&~WS_BORDER);
		}
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, NULL, curr_pos.x, curr_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
private:
	Static ship;
	POINT curr_pos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
