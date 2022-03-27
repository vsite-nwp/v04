#include "nwpwin.h"

//: prepare class ("STATIC") for a ship
class Static : public vsite::nwp::window 
{
public:
	std::string class_name() override { return "Static"; }
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		//: create ship if it doesn't exist yet
		//: change current location
		shipLocation = p;

		if (!ship)
			ship.create(*this, style1 | SS_CENTERIMAGE, "X", 0, p.x, p.y, shipY, shipX);

		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void on_key_up(int vk) override {
		//: mark ship (if exists) as "not moving"
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, style1);
			SetWindowPos(ship, 0, 0, 0, 0, 0, style2 | SWP_NOMOVE);
		}
	}

	void on_key_down(int vk) override {
		//: if ship exists, move it depending on key and mark as "moving"
		int shipSpeed = GetAsyncKeyState(VK_CONTROL) ? 30 : 15;
		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_LEFT:
			shipLocation.x = max(shipLocation.x - shipSpeed, rect.left);
			break;
		case VK_RIGHT:
			shipLocation.x = min(shipLocation.x + shipSpeed, rect.right - shipX);
			break;
		case VK_UP:
			shipLocation.y = max(shipLocation.y - shipSpeed, rect.top);
			break;
		case VK_DOWN:
			shipLocation.y = min(shipLocation.y + shipSpeed, rect.bottom - shipY);
			break;
		default:
			return;
		}

		SetWindowLong(ship, GWL_STYLE, style1 | WS_BORDER);
		SetWindowPos(ship, 0, shipLocation.x, shipLocation.y, 0, 0, style2);

	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT shipLocation;
	const int shipY = 30;
	const int shipX = 30;
	DWORD style1 = WS_CHILD | WS_VISIBLE | SS_CENTER;
	DWORD style2 = SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
