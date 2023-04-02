#include "nwpwin.h"

class Static : public vsite::nwp::window {
public:
	std::string class_name()override {
		return "Static";
	}
};

class main_window : public vsite::nwp::window
{
private:
	Static ship;
	POINT position;
	int speed = 5;

protected:
	void on_left_button_down(POINT p) override { 
		if (!ship) {
			ship.create(*this, WS_CHILD | SS_CENTER | WS_VISIBLE, "X", 1, p.x, p.y, 20, 15);
		}
		position = p;

		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	}
	void on_key_up(int vk) override {
		if (!ship) {return;}

		SetWindowLong(ship, GWL_STYLE, WS_CHILD | SS_CENTER | WS_VISIBLE);
		SetWindowPos(ship, 0, 0, 0, 0, 0,SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOSIZE);

	}
	void on_key_down(int vk) override {
		if (!ship) {return;}

		RECT windowsBorder;
		GetClientRect(*this, &windowsBorder);

		if (GetAsyncKeyState(VK_CONTROL)){speed = 20;}
		else {speed = 5;}

		switch (vk)
		{
		case 87:
		case VK_UP:
			
			if (windowsBorder.top < position.y - speed){position.y -= speed;}
			break;
		case 83:
		case VK_DOWN:
			if (windowsBorder.bottom - 15 > position.y + speed) { position.y += speed; }
			break;
		case 65:
		case VK_LEFT:
			if (windowsBorder.left < position.x - speed){position.x -= speed;}
			break;
		case 68:
		case VK_RIGHT:
			if (windowsBorder.right -20 > position.x + speed){position.x += speed;}
			break;
		default: 
			return;
		}

		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
