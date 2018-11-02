#define NOMINMAX
#include "nwpwin.h"
#include <algorithm>

class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 30, 30);
		::SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_position = p;
	}
	void OnKeyUp(int vk) {
		::SetWindowLong(ship, GWL_STYLE, current_style);
		::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		int steps = GetAsyncKeyState(VK_CONTROL) ? 20 : 5;
		RECT rc;
		::GetClientRect(*this, &rc);
		switch (vk) {
		case VK_UP:
			current_position.y = std::max(current_position.y - steps, rc.top);
			break;
		case VK_DOWN:
			current_position.y = std::min(current_position.y + steps, rc.bottom-30);
			break;
		case VK_LEFT:
			current_position.x = std::max(current_position.x - steps, rc.left);
			break;
		case VK_RIGHT:
			current_position.x = std::min(current_position.x + steps, rc.right-30);
			break;
		default:
			return;
		}
		::SetWindowLong(ship, GWL_STYLE, current_style | WS_BORDER);
		::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
	CONST DWORD current_style = WS_CHILD | WS_VISIBLE | SS_CENTER;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
