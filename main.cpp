#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship
#define WINDOWSIZE 16
class Static : public vsite::nwp::window {
private:
	bool ismoving = false;
public:
	std::string ClassName() {
		return "Static";
	}
	POINT shipCoordinates;
	const int shipMovement = 5;
};

class main_window : public vsite::nwp::window
{
protected:
	int shipMove = 0;
	void on_left_button_down(POINT p) override { 
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
		if (!ship) {
			ship.create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "X", 1, 0, 0, 15, 15);
			ship.shipCoordinates.x = p.x;
			ship.shipCoordinates.y = p.y;
		}
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | SS_CENTER | WS_VISIBLE);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {
		// TODO: mark ship (if exists) as "not moving"
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (ship) {
			RECT SizeOfWindow;
			GetClientRect(*this, &SizeOfWindow);
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | SS_CENTER | WS_VISIBLE | WS_BORDER);
			switch (vk) {
			case VK_CONTROL:
				if (shipMove > 0) shipMove = 0;
				else shipMove = 20;
				break;
			case VK_UP:
				if (ship.shipCoordinates.y - (ship.shipMovement + shipMove) <= SizeOfWindow.top)
					break;
				ship.shipCoordinates.y -= (ship.shipMovement + shipMove);
				break;
			case VK_DOWN:
				if (ship.shipCoordinates.y + (ship.shipMovement + shipMove) >= SizeOfWindow.bottom)
					break;
				ship.shipCoordinates.y += (ship.shipMovement + shipMove);
				break;
			case VK_LEFT:
				if (ship.shipCoordinates.x - (ship.shipMovement + shipMove) <= SizeOfWindow.left)
					break;
				ship.shipCoordinates.x -= (ship.shipMovement + shipMove);
				break;
			case VK_RIGHT:
				if (ship.shipCoordinates.x + (ship.shipMovement + shipMove) >= SizeOfWindow.right)
					break;
				ship.shipCoordinates.x += (ship.shipMovement + shipMove);
				break;
			}
			SetWindowPos(ship, 0, ship.shipCoordinates.x, ship.shipCoordinates.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
