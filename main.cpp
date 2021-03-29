#include "nwpwin.h"

class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "STATIC"; }
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		pozicija = p;
		if (!ship)
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, pozicija.x, pozicija.y, 30, 30);

		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pozicija = p;
	}
	void on_key_up(int vk) override {
		if (ship)
		{
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, pozicija.x, pozicija.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

		}
	}
	void on_key_down(int vk) override {
		if (ship) {
			int MoveSpeed = 5;
			if (GetKeyState(VK_CONTROL) < 0)
				MoveSpeed += 80;
			RECT ship_r;
			GetClientRect(*this, &ship_r);
			switch (vk) {
			case VK_UP:
				pozicija.y = max(ship_r.top, pozicija.y - MoveSpeed);
				break;
			case VK_DOWN:
				pozicija.y = min(ship_r.bottom - 20, pozicija.y + MoveSpeed);
				break;
			case VK_LEFT:
				pozicija.x = max(ship_r.left, pozicija.x - MoveSpeed);
				break;
			case VK_RIGHT:
				pozicija.x = min(ship_r.right - 20, pozicija.x + MoveSpeed);
				break;
			default: return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, 0, pozicija.x, pozicija.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT pozicija;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}