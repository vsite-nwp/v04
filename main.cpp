#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship
class label: public vsite::nwp::window{
	std::string class_name() override {
		return "STATIC";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		
		position = p;
		if (!l)
			l.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 1, position.x, position.y, 20, 20);

		SetWindowPos(l, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;


		
		
	}
	void on_key_up(int vk) override {
		
		if (l) {
			SetWindowLong(l, GWL_STYLE, WS_CHILD | WS_VISIBLE|SS_CENTER);
			SetWindowPos(l, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		
		if (l) {
			int MoveSp = 3;
			if (GetAsyncKeyState(VK_CONTROL) < 0)
				MoveSp += 55;
			RECT ship;
			GetClientRect(*this, &ship);

			switch (vk)
			{
			case VK_UP:
				position.y = max(ship.top, position.y - MoveSp);
				break;
			case VK_DOWN:
				position.y = min(ship.bottom - 20, position.y + MoveSp);
				break;
			case VK_LEFT:
				position.x = max(ship.left, position.x - MoveSp);
				break;
			case VK_RIGHT:
				position.x = min(ship.right - 20, position.x + MoveSp);
				break;
			default: return;


			}
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	POINT position;
	label l;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
