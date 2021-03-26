#include "nwpwin.h"
using namespace vsite::nwp;

class STATIC : public window {
public:
	std::string class_name() override { return "STATIC"; }
};

class main_window : public window
{
protected:
	void on_left_button_down(POINT p) override {
		if (!ship) {
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		}
		else
		{
			SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}
		position = p;
	}
	void on_key_up(int vk) override {
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER );
		SetWindowPos(ship, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED |SWP_NOSIZE | SWP_NOMOVE);
	}
	void on_key_down(int vk) override {
		
		if (!ship) return;

		RECT r; GetClientRect(*this, &r);
		int s = GetAsyncKeyState(VK_CONTROL) ? 100 : 10;

		switch (vk) {
		case VK_UP:
			position.y = max(position.y - s, r.top);
			break;
		case VK_DOWN:
			position.y = min(position.y + s, r.bottom - 20);
			break;
		case VK_LEFT:
			position.x = max(position.x - s, r.left);
			break;
		case VK_RIGHT:
			position.x = min(position.x + s, r.right - 20);
			break;
		}
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	STATIC ship;
	POINT position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
