#include "nwpwin.h"

#define SHIP_SIZE 20

class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, SHIP_SIZE, SHIP_SIZE);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		point = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		RECT rc;
		GetClientRect(*this, &rc);
		int vel = GetAsyncKeyState(VK_CONTROL) ? 15 : 5;

		switch (vk)
		{
			case VK_UP:
				point.y = max(point.y - vel, 0);
				break;
			case VK_DOWN:
				point.y = min(point.y + vel, rc.bottom - SHIP_SIZE);
				break;
			case VK_LEFT:
				point.x = max(point.x - vel, 0);
				break;
			case VK_RIGHT:
				point.x = min(point.x + vel, rc.right - SHIP_SIZE);
				break;
			default:
				return;
		}
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
		SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);

	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	POINT point;
	Static ship;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
