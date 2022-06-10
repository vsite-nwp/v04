#include "nwpwin.h"

// : prepare class ("STATIC") for a ship

class STATIC : public vsite::nwp::window {
public:
	std::string class_name()override {
		return "Static";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
		ship_pos = p;
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, shipY, shipX);
		}
	}
	void on_key_up(int vk) override {
		// TODO: mark ship (if exists) as "not moving"
	}
	void on_key_down(int vk) override {
		// TODO: if ship exists, move it depending on key and mark as "moving"
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
