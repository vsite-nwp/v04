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
		current_position = p;
		if (!ship)
		{
			ship.Create(*this, SHIP_STYLE, "X", 1, current_position.x, current_position.y, SHIP_WIDTH, SHIP_HEIGHT);
		}
		else {
			::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, SHIP_STYLE);
			SetWindowPos(ship, NULL, NULL, NULL, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			int momentum = GetKeyState(VK_CONTROL) < 0 ? 20 : 5;
			RECT window_rect;

			GetClientRect(*this, &window_rect);
			RECT ship_rect;

			GetClientRect(ship, &ship_rect);
			switch (vk) {
			case VK_UP:
				current_position.y = max(current_position.y - momentum, 0);
				break;
			case VK_DOWN:
				current_position.y = min(current_position.y + momentum, window_rect.bottom - SHIP_HEIGHT);
				break;
			case VK_LEFT:
				current_position.x = max(current_position.x - momentum, 0);
				break;
			case VK_RIGHT:
				current_position.x = min(current_position.x + momentum, window_rect.right - SHIP_HEIGHT);
				break;
			}
			SetWindowLong(ship, GWL_STYLE, SHIP_STYLE | WS_BORDER);
			SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	const int SHIP_WIDTH = 20;
	const int SHIP_HEIGHT = 20;
	const long SHIP_STYLE = WS_CHILD | WS_VISIBLE | SS_CENTER;
	POINT current_position;
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow) {
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
};
