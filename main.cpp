#include "nwpwin.h"

// prepare class ("STATIC") for a ship
class ship : public vsite::nwp::window {
public:
	std::string class_name()override {
		return "Static";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		// create ship if it doesn't exist yet
		// change current location
		if (!x) {
			x.create(*this, WS_CHILD|WS_VISIBLE, "X", 1, p.x, p.y, 11, 17);
		}
		else {
			SetWindowPos(x, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		current_pos = p;
		style = GetWindowLong(x, GWL_STYLE);
	}
	void on_key_up(int vk) override {
		// mark ship (if exists) as "not moving"
		if (!x) return;
		SetWindowLong(x, GWL_STYLE, style);
		SetWindowPos(x, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		speed = 1;
	}
	void on_key_down(int vk) override {
		// if ship exists, move it depending on key and mark as "moving"
		RECT wndSize;
		GetClientRect(*this, &wndSize);
		if (GetKeyState(VK_CONTROL) < 0) speed = 2;

		if (!x) return;
		else {
			switch (vk) {
				case VK_UP:
					if (wndSize.top < current_pos.y) current_pos.y -= move * speed;
					break;
				case VK_DOWN:
					if (wndSize.bottom > current_pos.y + 17) current_pos.y += move * speed;
					break;
				case VK_LEFT:
					if (wndSize.left < current_pos.x) current_pos.x -= move * speed;
					break;
				case VK_RIGHT:
					if (wndSize.right > current_pos.x + 11) current_pos.x += move * speed;
					break;
				default:
					return;
			}
		}
		SetWindowPos(x, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		SetWindowLong(x, GWL_STYLE, style + WS_BORDER);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	ship x;
	int move = 4;
	int speed = 1;
	POINT current_pos;
	LONG style;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
