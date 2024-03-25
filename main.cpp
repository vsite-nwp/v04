#include "nwpwin.h"

class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }
};

static const int size = 20;
static const DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override
	{
		ship_pos = p;

		if (!ship)
			ship.create(*this, style, "x", 0, p.x, p.y, size, size);
		else
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void on_key_up(int vk) override
	{
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;

		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
	}

	void on_key_down(int key) override
	{
		RECT window_border;
		GetClientRect(*this, &window_border);

		int speed = GetAsyncKeyState(VK_CONTROL) ? 50 : 10;

		if (ship)
		{
			switch (key)
			{
			case VK_UP:
				ship_pos.y = max(ship_pos.y - speed, window_border.top);
				break;
			case VK_DOWN:
				ship_pos.y = min(ship_pos.y + speed, window_border.bottom - size);
				break;
			case VK_LEFT:
				ship_pos.x = max(ship_pos.x - speed, window_border.left);
				break;
			case VK_RIGHT:
				ship_pos.x = min(ship_pos.x + speed, window_border.right - size);
				break;
			default:
				return;
			}

			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style |= WS_BORDER;

			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, ship_pos.x, ship_pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}

	void on_destroy() override
	{
		::PostQuitMessage(0);
	}

private:
	Static ship;
	POINT ship_pos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
