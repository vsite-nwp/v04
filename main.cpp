#include "nwpwin.h"

//- klasa `STATIC` je za sve "STATIC" prozore, prebacite ostale membere u `main_window`
//
//- uputstva kažu da "dok se drži" Ctrl tipka brod ide brže - ne da Ctrl uključuje / isključuje "warp" (koristite `GetAsyncKeyState`)
//
//	- ne treba vam promjena stila na `on_left_button_down`
//
//	- _brod_ dobije border na svaku tipku, ne samo dok se krece
//
//	- ponašanje na rubovima nije konzistentno(a i zakomplicirali ste taj kod, sve movement i power_up varijable mogu biti lokalne)
//
//	- ako se postavi pozicija broda mišem, a nakon toga koriste strelice - dogodi se veliki skok
//
//	- ne morate POINT kopirati clan po clan


class STATIC : public vsite::nwp::window {
public:
	std::string class_name() {
		return "STATIC";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	POINT ship_coordinates;
	const int ship_movement = 5;
	int ship_move_powerup = 0;
	void on_left_button_down(POINT p) override {
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE, "x", 1, 0, 0, 15, 15);
		}
		ship_coordinates.x = p.x;
		ship_coordinates.y = p.y;
		SetWindowLong(ship, 0, WS_CHILD | WS_VISIBLE | SS_CENTER);
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
			if (GetAsyncKeyState(VK_CONTROL)) ship_move_powerup = 15;
			else ship_move_powerup = 0;

			switch (vk) {
			case VK_LEFT:
				if (ship_coordinates.x - (ship_movement + ship_move_powerup) <= parent_window_size.left)
					break;
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
				ship_coordinates.x -= (ship_movement + ship_move_powerup);
				break;
			case VK_RIGHT:
				if (ship_coordinates.x + (ship_movement + ship_move_powerup) >= parent_window_size.right - 12)
					break;
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
				ship_coordinates.x += (ship_movement + ship_move_powerup);
				break;
			case VK_DOWN:
				if (ship_coordinates.y + (ship_movement + ship_move_powerup) >= parent_window_size.bottom - 12)
					break;
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
				ship_coordinates.y += (ship_movement + ship_move_powerup);
				break;
			case VK_UP:
				if (ship_coordinates.y - (ship_movement + ship_move_powerup) <= parent_window_size.top)
					break;
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
				ship_coordinates.y -= (ship_movement + ship_move_powerup);
				break;
			}
			
			SetWindowPos(ship, 0, ship_coordinates.x, ship_coordinates.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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
