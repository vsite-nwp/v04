#include "nwpwin.h"

using namespace std;

const int shipSize = 20;

class STATIC : public vsite::nwp::window {

public:
	string class_name() override {
		return "static";
	}
};

class main_window : public vsite::nwp::window
{
	STATIC ship;
	POINT location;

protected:
	void on_left_button_down(POINT p) override { 
		

		location = p;
		
		if (!ship) {
			ship.create(*this, WS_VISIBLE | WS_CHILD | SS_CENTER, "X", 0, location.x, location.y, shipSize, shipSize);
		}

		SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {

		DWORD style = GetWindowLong(ship, GWL_STYLE);

		if (ship) {
			SetWindowLong(ship, GWL_STYLE, style &~WS_BORDER);

			SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}

	}
	void on_key_down(int vk) override {  

		RECT rc;
		GetClientRect(*this, &rc);
		short key_press = GetAsyncKeyState(VK_CONTROL);
		int speed;
		

		if (key_press < 0)
			speed = 30;
		else
			speed = 3;

		switch (vk) {
		case VK_UP:
			if(location.y>0 && (location.y-speed)>=0)
				location.y -= speed;
			break;
		case VK_DOWN:
			if(((location.y + shipSize) + speed) <= rc.bottom)
				location.y += speed;
			break;
		case VK_LEFT:
			if(location.x>0 && (location.x - speed) >= 0)
				location.x -= speed;
			break;
		case VK_RIGHT:
			if(((location.x + shipSize) + speed)  <= rc.right)
				location.x += speed;
			break;

		default:
			return;
		}

		DWORD style = GetWindowLong(ship, GWL_STYLE);

		SetWindowLong(ship, GWL_STYLE, style|WS_BORDER);
		SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

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