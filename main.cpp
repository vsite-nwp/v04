#include "nwpwin.h"



class Static : public vsite::nwp::window {
public:
	std::string class_name()override {
		return "Static";
	}
};

class main_window : public vsite::nwp::window
{
	Static ship;
	POINT pos;
protected:
	void on_left_button_down(POINT p) override {


		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 1, p.x, p.y, 30, 30);
		}
		pos = p;

		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void on_key_up(int vk) override {

		if (!ship) {
			
			return;
		}
		int style = GetWindowLong(ship, GWL_STYLE) & ~WS_BORDER;
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
	}

	void on_key_down(int vk) override {

		if (!ship) {
			
			return;
		}
		int style = GetWindowLong(ship, GWL_STYLE) | WS_BORDER;
		RECT winBorder;
		GetClientRect(*this, &winBorder);
		//Normal move: 10
		//CTRL move: 20 
		int move = GetAsyncKeyState(VK_CONTROL) ? 20 : 10;

		switch (vk) {
		case VK_LEFT:
			pos.x = max(pos.x - move, 0);
			break;

		case VK_RIGHT:
			pos.x = min(pos.x + move, winBorder.right - 30);
			break;

		case VK_UP:
			pos.y = max(pos.y - move, 0);
			break;

		case VK_DOWN:
			pos.y = min(pos.y + move, winBorder.bottom - 30);
			break;
		}

		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);

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
