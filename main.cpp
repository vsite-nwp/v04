#include "nwpwin.h"

class Static : public vsite::nwp::window {
protected:
	std::string class_name() override {

		return "STATIC";
	}
};
class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override {

		position = p;
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "X", 0, p.x, p.y, 20,20);
		}


		SetWindowPos(ship, HWND_TOP, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void on_key_up(int vk) override {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, style);

			SetWindowPos(ship, NULL, NULL, NULL, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE);
		}
	}
	void on_key_down(int vk) override {
		int ship_step = ::GetAsyncKeyState(VK_CONTROL) ? 20 : 10;
		RECT window_rect;
		GetClientRect(*this, &window_rect);
		switch (vk) {


		case VK_UP:
			position.y = max(0, position.y - ship_step);
			break;
		case VK_DOWN:
			position.y = min(window_rect.bottom - 30, position.y + ship_step);
			break;
		case VK_LEFT:
			position.x = max(0, position.x - ship_step);

			break;
		case VK_RIGHT:
			position.x = min(window_rect.right - 30, position.x + ship_step);

			break;
		default:

			return;
		}
		SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;

	const int style = WS_CHILD | WS_VISIBLE | SS_CENTER;

	POINT position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
