#include "nwpwin.h"
#define SHIP_LENGTH 20
class Static :public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, SHIP_LENGTH, SHIP_LENGTH);
		else
			SetWindowPos(ship, *this, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_position = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			DWORD current_style = GetWindowLong(ship, GWL_STYLE);
			SetWindowLong(ship, GWL_STYLE, current_style & ~WS_BORDER);
			SetWindowPos(ship, *this, current_position.x, current_position.y, 0, 0,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		bool ctrl = GetAsyncKeyState(VK_CONTROL);
		RECT main_rect;
		GetClientRect(*this, &main_rect);
		const int step = ctrl ? 5 : 1;
		switch (vk) {
		case VK_UP:
			current_position.y = max(current_position.y - step, main_rect.top);
			break;
		case VK_DOWN:
			current_position.y = min(current_position.y + step, main_rect.bottom - SHIP_LENGTH);
			break;
		case VK_LEFT:
			current_position.x = max(current_position.x - step, main_rect.left);
			break;
		case VK_RIGHT:
			current_position.x = min(current_position.x + step, main_rect.right - SHIP_LENGTH);
			break;
		default:
			return;
		}

		DWORD current_style = GetWindowLong(ship, GWL_STYLE);
		SetWindowLong(ship, GWL_STYLE, WS_BORDER | current_style);
		SetWindowPos(ship, *this, current_position.x, current_position.y, 0, 0,
			SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
