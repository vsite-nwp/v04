#include "nwpwin.h"
#define SHIP_LENGTH 20
class Static :public Window
{
public:
	bool isMoving = false;
	std::string ClassName() override { return "STATIC"; }
};

struct Step {
	const int slow = 1;
	const int fast = 5;
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
		if (ship && ship.isMoving) {
			DWORD current_style = GetWindowLong(ship, GWL_STYLE);
			SetWindowLong(ship, GWL_STYLE, current_style ^ WS_BORDER);
			SetWindowPos(ship, *this, current_position.x, current_position.y, 0, 0,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
			ship.isMoving = false;
		}
	}
	void OnKeyDown(int vk) {
		bool ctrl = GetAsyncKeyState(VK_CONTROL);
		RECT main_rect;
		GetClientRect(*this, &main_rect);
		Step step;
		switch (vk) {
		case VK_UP:
			if (ctrl)
				current_position.y -= step.fast;
			current_position.y -= step.slow;
			current_position.y = max(current_position.y, main_rect.top);
			break;
		case VK_DOWN:
			if (ctrl)
				current_position.y += step.fast;
			current_position.y += step.slow;
			current_position.y = min(current_position.y, main_rect.bottom - SHIP_LENGTH);
			break;
		case VK_LEFT:
			if (ctrl)
				current_position.x -= step.fast;
			current_position.x -= step.slow;
			current_position.x = max(current_position.x, main_rect.left);
			break;
		case VK_RIGHT:
			if (ctrl)
				current_position.x += step.fast;
			current_position.x += step.slow;
			current_position.x = min(current_position.x, main_rect.right - SHIP_LENGTH);
			break;
		}

		if (vk == VK_UP || vk == VK_DOWN || vk == VK_LEFT || vk == VK_RIGHT) {
			ship.isMoving = true;
			DWORD current_style = GetWindowLong(ship, GWL_STYLE);
			SetWindowLong(ship, GWL_STYLE, WS_BORDER | current_style);
			SetWindowPos(ship, *this, current_position.x, current_position.y, 0, 0,
				SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
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
