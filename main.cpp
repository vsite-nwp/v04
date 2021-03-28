#include "nwpwin.h"

#define WINDOWSIZE 16
class Static : public vsite::nwp::window {
public:
	std::string class_name() {
		return "Static";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	int shipMove = 0;
	POINT shipCoordinates;
	const int shipMovement = 5;
	void on_left_button_down(POINT p) override {
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 1, 0, 0, 15, 15);
		}
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		shipCoordinates = p;
	}
	void on_key_up(int vk) override {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		if (ship) {
			RECT SizeOfWindow;
			GetClientRect(*this, &SizeOfWindow);
			if (GetAsyncKeyState(VK_CONTROL))
				shipMove = 10;
			else
				shipMove = 0;
			switch (vk) {
			case VK_UP:
				if (shipCoordinates.y - (shipMovement + shipMove) <= SizeOfWindow.top) {
					shipCoordinates.y = SizeOfWindow.top;
					break;
				}
				shipCoordinates.y -= (shipMovement + shipMove);
				break;
			case VK_DOWN:
				if (shipCoordinates.y + (shipMovement + shipMove) >= SizeOfWindow.bottom - 15) {
					shipCoordinates.y = SizeOfWindow.bottom - 15;
					break;
				}
				shipCoordinates.y += (shipMovement + shipMove);
				break;
			case VK_LEFT:
				if (shipCoordinates.x - (shipMovement + shipMove) <= SizeOfWindow.left) {
					shipCoordinates.x = SizeOfWindow.left;
					break;
				}
				shipCoordinates.x -= (shipMovement + shipMove);
				break;
			case VK_RIGHT:
				if (shipCoordinates.x + (shipMovement + shipMove) >= SizeOfWindow.right - 15) {
					shipCoordinates.x = SizeOfWindow.right - 15;
					break;
				}
				shipCoordinates.x += (shipMovement + shipMove);
				break;
			default: return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(ship, 0, shipCoordinates.x, shipCoordinates.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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
