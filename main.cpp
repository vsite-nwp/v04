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
			x.create(*this, WS_CHILD|WS_VISIBLE, "X", 1, p.x, p.y, width, height);
		}
		else {
			SetWindowPos(x, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		current_pos = p;
	}
	void on_key_up(int vk) override {
		// mark ship (if exists) as "not moving"
		if (!x) return;
		if ((GetWindowLong(x, GWL_STYLE) & WS_BORDER)) SetWindowLong(x, GWL_STYLE, GetWindowLong(x, GWL_STYLE) & ~WS_BORDER);
		SetWindowPos(x, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
	}
	void on_key_down(int vk) override {
		// if ship exists, move it depending on key and mark as "moving"
		if (!x) return;
		RECT wndSize;
		GetClientRect(*this, &wndSize);
		if (!(GetWindowLong(x, GWL_STYLE) & WS_BORDER)) SetWindowLong(x, GWL_STYLE, GetWindowLong(x, GWL_STYLE) | WS_BORDER);
		SetWindowPos(x, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		int move = GetKeyState(VK_CONTROL) < 0 ? 8 : 4;
		switch (vk) {
			case VK_UP:
				current_pos.y = wndSize.top < current_pos.y - move ? current_pos.y - move : wndSize.top;
				break;
			case VK_DOWN:
				current_pos.y = wndSize.bottom > current_pos.y + height + move ? current_pos.y + move : wndSize.bottom - height;
				break;
			case VK_LEFT:
				current_pos.x = wndSize.left < current_pos.x - move ? current_pos.x - move : wndSize.left;
				break;
			case VK_RIGHT:
				current_pos.x = wndSize.right > current_pos.x + width + move ? current_pos.x + move : wndSize.right - width;
				break;
			default:
				return;
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	ship x;
	POINT current_pos;
	static const int width = 11;
	static const int height = 17;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
