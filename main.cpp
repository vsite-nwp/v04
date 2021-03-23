#include "nwpwin.h"

class STATIC : public vsite::nwp::window {
public:
	std::string class_name() {
		return "STATIC";
	}

	POINT ship_coordinates;
	const int ship_movement = 5;
};

class main_window : public vsite::nwp::window
{
protected:
	int ship_move_powerup = 0;
	void on_left_button_down(POINT p) override {
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE, "x", 1, 0, 0, 15, 15);
			ship.ship_coordinates.x = p.x;
			ship.ship_coordinates.y = p.y;
		}
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		if (ship) {
			RECT parent_window_size;
			GetClientRect(*this, &parent_window_size);
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);

			switch (vk) {
			case VK_CONTROL:
				if (ship_move_powerup > 0) ship_move_powerup = 0;
				else ship_move_powerup = 20;
				break;
			case VK_LEFT:
				if (ship.ship_coordinates.x - (ship.ship_movement + ship_move_powerup) <= parent_window_size.left)
					break;
				ship.ship_coordinates.x -= (ship.ship_movement + ship_move_powerup);
				break;
			case VK_RIGHT:
				if (ship.ship_coordinates.x + (ship.ship_movement + ship_move_powerup) >= parent_window_size.right)
					break;
				ship.ship_coordinates.x += (ship.ship_movement + ship_move_powerup);
				break;
			case VK_DOWN:
				if (ship.ship_coordinates.y + (ship.ship_movement + ship_move_powerup) >= parent_window_size.bottom)
					break;
				ship.ship_coordinates.y += (ship.ship_movement + ship_move_powerup);
				break;
			case VK_UP:
				if (ship.ship_coordinates.y - (ship.ship_movement + ship_move_powerup) <= parent_window_size.top)
					break;
				ship.ship_coordinates.y -= (ship.ship_movement + ship_move_powerup);
				break;
			}

			SetWindowPos(ship, 0, ship.ship_coordinates.x, ship.ship_coordinates.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	STATIC ship;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
