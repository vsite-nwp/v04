#include "nwpwin.h"

class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }
};

class main_window : public vsite::nwp::window
{
private:
	Static ship;
	POINT position;
	static const DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;

protected:
	void on_left_button_down(POINT p) override { 

		if (!ship)
		{
			ship.create(*this, style, "X", 0, p.x, p.y, 30, 20);
		}
		
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void on_key_up(int vk) override {
		
		if (ship)
		{
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {

		int ctrl = GetAsyncKeyState(VK_CONTROL) ? 10 : 5;
		RECT rect;
		GetClientRect(*this, &rect);

		if (ship)
		{
			switch (vk)
			{
			case VK_LEFT:
				position.x = max(position.x - ctrl, rect.left);
				break;
			case VK_UP:
				position.y = max(position.y - ctrl, rect.top);
				break;
			case VK_RIGHT:
				position.x = min(position.x + ctrl, rect.right - 30); 
				break;
			case VK_DOWN:
				position.y = min(position.y + ctrl, rect.bottom - 20);
				break;
			default:
				return;
			}
		}
		SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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
