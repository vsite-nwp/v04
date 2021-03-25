#include "nwpwin.h"

class STATIC : public vsite::nwp::window{public:std::string class_name() override { return "STATIC"; }};
class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		if (!s) {
			s.create(*this, style, "Brodic\nCHOO CHOO", 0, p.x, p.y, 50, 50);
		}
		SetWindowPos(s, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pos = p;
	}
	void on_key_up(int vk) override {
		if (s) {
			SetWindowLong(s, GWL_STYLE, style);
			SetWindowPos(s, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		int warp_speed = GetAsyncKeyState(VK_CONTROL) ? 100 : 1;
		RECT rect;
		GetClientRect(*this, &rect);

		if (s)
		{
			switch (vk)
			{
			case VK_LEFT:
				pos.x = max(pos.x - warp_speed, rect.left);
				break;
			case VK_UP:
				pos.y = max(pos.y - warp_speed, rect.top);
				break;
			case VK_RIGHT:
				pos.x = min(pos.x + warp_speed, rect.right - 50);
				break;
			case VK_DOWN:
				pos.y = min(pos.y + warp_speed, rect.bottom - 50);
				break;
			default:
				return;
			}
		}

		SetWindowLong(s, GWL_STYLE, style | WS_BORDER);
		SetWindowPos(s, 0, pos.x, pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	STATIC s;
	POINT pos;
	static const int style = WS_CHILD | WS_VISIBLE | SS_CENTER;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
