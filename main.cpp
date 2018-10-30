#include "nwpwin.h"

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
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, 20, 20);
		else
			SetWindowPos(ship, *this, p.x, p.y, 20, 20, SWP_NOSIZE | SWP_NOZORDER);
		current_position = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, *this, current_position.x, current_position.y, 20, 20,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}

	}
	void OnKeyDown(int vk) {
		bool ctrl = GetAsyncKeyState(VK_CONTROL);
		GetClientRect(*this, &main_rect);
		switch (vk) {
		case VK_UP:
			if (ctrl)
				current_position.y -= 5;
			current_position.y -= 1;
			break;
		case VK_DOWN:
			if (ctrl)
				current_position.y += 5;
			current_position.y += 1;
			break;
		case VK_LEFT:
			if (ctrl)
				current_position.x -= 5;
			current_position.x -= 1;
			break;
		case VK_RIGHT:
			if (ctrl)
				current_position.x += 5;
			current_position.x += 1;
			break;
		}

		if (current_position.x > main_rect.right - 20)
			current_position.x = main_rect.right - 20;
		else if (current_position.y > main_rect.bottom - 20)
			current_position.y = main_rect.bottom - 20;
		else if (current_position.x < 0)
			current_position.x = 0;
		else if (current_position.y < 0)
			current_position.y = 0;

		SetWindowPos(ship, *this, current_position.x, current_position.y, 20, 20,
			SWP_NOSIZE | SWP_NOZORDER);
		DWORD current_style = GetWindowLong(ship, GWL_STYLE);
		SetWindowLong(ship, GWL_STYLE, WS_BORDER | current_style);
		SetWindowPos(ship, *this, current_position.x, current_position.y, 20, 20,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
	RECT main_rect;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
