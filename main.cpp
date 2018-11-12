#include "nwpwin.h"

class Static : public Window {
protected:
	std::string ClassName() override { return "STATIC"; };
};

class MainWindow : public Window
{
private:
	const int style = WS_CHILD | WS_VISIBLE | SS_CENTER | BS_CENTER;
	Static ship;
	POINT current_position;
protected:
	void OnLButtonDown(POINT p) {
		current_position = p;
		if (!ship)
			ship.Create(*this, style, "X", 0, p.x, p.y, 30, 30);
		
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_position = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, NULL, NULL, NULL, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE);
		}
	}
	void OnKeyDown(int vk) {
		int steps = ::GetAsyncKeyState(VK_CONTROL) ? 20 : 5;
		
		RECT window_rect;
		GetClientRect(*this, &window_rect);

		switch (vk) {
			case VK_UP: 
				current_position.y = max(0, current_position.y - steps); break;
			case VK_DOWN: 
				current_position.y = min(window_rect.bottom - 30, current_position.y + steps); break;
			case VK_LEFT: 
				current_position.x = max(0, current_position.x - steps); break;
			case VK_RIGHT: 
				current_position.x = min(window_rect.right - 30, current_position.x + steps); break;
			default: return;
		}
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
		SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
