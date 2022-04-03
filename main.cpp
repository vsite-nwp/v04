#include "nwpwin.h"

//: prepare class ("STATIC") for a ship
class Static : public vsite::nwp::window 
{
public:
	std::string class_name() override { return "Static"; }
};

const int shipY = 30;
const int shipX = 30;

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		//: create ship if it doesn't exist yet
		//: change current location
		shipLocation = p;

		if (!ship)
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , "X", 0, p.x, p.y, shipY, shipX);

		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void on_key_up(int vk) override {
		//: mark ship (if exists) as "not moving"
		if (ship) {
			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style &= ~WS_BORDER;
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
		}
	}

	void on_key_down(int vk) override {
		//: if ship exists, move it depending on key and mark as "moving"
		int shipSpeed = GetKeyState(VK_CONTROL)<0 ? 30 : 15;
		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_LEFT:
			shipLocation.x = shipLocation.x - shipSpeed;
			// leaves screen on left side appears on right
			if (shipLocation.x < 0) {
				shipLocation.x = rect.right;
			}
			break;
		case VK_RIGHT:
			shipLocation.x = shipLocation.x + shipSpeed;
			// leaves screen on right side appears on left
			if (shipLocation.x > rect.right) {
				shipLocation.x = 0;
			}
			break;
		case VK_UP:
			shipLocation.y = shipLocation.y - shipSpeed;
			// leaves screen on top side appears on bottom
			if (shipLocation.y < 0)
				shipLocation.y = rect.bottom;
			break;
		case VK_DOWN:
			shipLocation.y = shipLocation.y + shipSpeed;
			// leaves screen on bottom side appears on top
			if (shipLocation.y > rect.bottom)
				shipLocation.y = 0;
			break;
		default:
			return; //we don want border to show for every key
		}
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style |= WS_BORDER;
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, shipLocation.x, shipLocation.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT shipLocation;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
