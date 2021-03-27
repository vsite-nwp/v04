#include "nwpwin.h"

class Static : public vsite::nwp::window {
public:
	std::string class_name() override { return "Static"; }
};

class main_window : public vsite::nwp::window
{
private:
	Static ship;
	POINT shipPosition;
	const int shipHeight = 30;
	const int shipWidth = 30;

protected:
	void on_left_button_down(POINT p) override {
		shipPosition = p;

		if (!ship)
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, "X", 0, p.x, p.y, shipHeight, shipWidth);

		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void on_key_up(int vk) override {

		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}

	void on_key_down(int vk) override {

		int shipSpeed = GetAsyncKeyState(VK_CONTROL) ? 20 : 10;
		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_LEFT:
			shipPosition.x = max(shipPosition.x - shipSpeed, rect.left);
			break;
		case VK_UP:
			shipPosition.y = max(shipPosition.y - shipSpeed, rect.top);
			break;
		case VK_RIGHT:
			shipPosition.x = min(shipPosition.x + shipSpeed, rect.right - shipWidth);
			break;
		case VK_DOWN:
			shipPosition.y = min(shipPosition.y + shipSpeed, rect.bottom - shipHeight);
			break;
		default:
			return;
		}

		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(ship, 0, shipPosition.x, shipPosition.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

	void on_destroy() override {
		::PostQuitMessage(0);
	}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
