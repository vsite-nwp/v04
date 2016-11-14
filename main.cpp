#include "nwpwin.h"
#define SHIP_MOVE 5
#define SHIP_FAST_MOVE 20
#define SHIP_SIZE 20

class Static :public Window {
public:
	std::string ClassName() override { return "Static"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, 0, 0, SHIP_SIZE, SHIP_SIZE);
		this->p = p;
		Move();
	}
	void OnKeyUp(int vk) {
		if (!ship) return;
		Move();
	}
	void OnKeyDown(int vk) {
		if (!ship) return;

		RECT rect;
		::GetClientRect(*this, &rect);
		step = GetKeyState(VK_CONTROL) < 0 ? SHIP_MOVE : SHIP_FAST_MOVE;
		switch (vk) {
		case VK_UP:
			p.y = max(0, p.y - step);
			break;
		case VK_DOWN:
			p.y = min(rect.bottom - SHIP_SIZE, p.y + step);
			break;
		case VK_LEFT:
			p.x = max(0, p.x - step);
			break;
		case VK_RIGHT:
			p.x = min(rect.right - SHIP_SIZE, p.x + step);
			break;
		default:
			break;
		}
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT p;
	int step;
	void Move() {
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
