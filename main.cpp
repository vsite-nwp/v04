#include "nwpwin.h"


int const shipSize = 20;

class Static : public vsite::nwp::window {
public:
	std::string class_name() override { return "STATIC"; }
};

class main_window : public vsite::nwp::window
{

protected:
	void on_left_button_down(POINT p) override {
		
		pos = p;
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER, "X", 0, p.x, p.y, shipSize, shipSize); 
		}
			
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE);
	}
	void on_key_down(int vk) override {
		if (ship) {
			RECT movement;

			int Speed = GetKeyState(VK_CONTROL) <0 ? 30 : 5;
			GetClientRect(*this, &movement);
			switch (vk) {
			case VK_UP:
				pos.y = max(movement.top, pos.y - Speed);
				break;
			case VK_DOWN:
				pos.y = min(movement.bottom-shipSize, pos.y + Speed);
				break;
			case VK_LEFT:
				pos.x = max(movement.left, pos.x - Speed);
				break;
			case VK_RIGHT:
				pos.x = min(movement.right-shipSize, pos.x + Speed);
				break;
			default: return;
			}
			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style |= WS_BORDER;
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT pos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
