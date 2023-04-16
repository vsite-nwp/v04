#include <algorithm>

#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship
class ship : public vsite::nwp::window
{
public:
	std::string class_name() override
	{
		return "STATIC";
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		// create ship if it doesn't exist yet
		if (!player_ship) 
		{
			player_ship.create(*this, 
				WS_CHILD | WS_VISIBLE, 
				"X", 
				1, 
				p.x, 
				p.y, 
				width, 
				height);
		}

		// change current location
		else 
		{
			SetWindowPos(player_ship, 
				0, 
				p.x, 
				p.y, 
				0, 
				0, 
				SWP_NOSIZE | SWP_NOZORDER);
		}

		player_ship_position = p;
	}

	void on_key_up(int vk) override {
		// mark ship (if exists) as "not moving"
		if ((GetWindowLong(player_ship, GWL_STYLE) & WS_BORDER))
		{
			SetWindowLong(player_ship, GWL_STYLE, GetWindowLong(player_ship, GWL_STYLE) & ~WS_BORDER);
		}

		SetWindowPos(player_ship,
			0, 
			player_ship_position.x,
			player_ship_position.y,
			0, 
			0, 
			SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
	}

	void on_key_down(int vk) override {
		// if ship exists, move it depending on key and mark as "moving"
		if (!player_ship)
			return;

		RECT window_size;
		GetClientRect(*this, &window_size);

		if (!(GetWindowLong(player_ship, GWL_STYLE) & WS_BORDER))
		{
			SetWindowLong(player_ship, 
				GWL_STYLE, 
				GetWindowLong(player_ship, GWL_STYLE) | WS_BORDER);
		}

		SetWindowPos(player_ship, 
			0, 
			player_ship_position.x, 
			player_ship_position.y, 
			0, 
			0, 
			SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

		int move = GetKeyState(VK_CONTROL) < 0 ? 10 : 10;

		switch (vk)
		{
		case VK_UP:
			player_ship_position.y = std::clamp(player_ship_position.y - move, window_size.top, window_size.bottom);
			break;
		case VK_DOWN:
			player_ship_position.y = std::clamp(player_ship_position.y + move, window_size.top, window_size.bottom - height);
			break;
		case VK_LEFT:
			player_ship_position.x = std::clamp(player_ship_position.x - move, window_size.left, window_size.right);
			break;
		case VK_RIGHT:
			player_ship_position.x = std::clamp(player_ship_position.x + move, window_size.left, window_size.right - width);
			break;
		default:
			return;
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}

private:
	ship player_ship;
	POINT player_ship_position;

	static const int width = 16;
	static const int height = 16;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
