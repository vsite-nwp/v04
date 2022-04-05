#include "nwpwin.h"

// prepared class ("STATIC") for a ship
class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }
};

static const int ShipSize = 20;
static const DWORD style1 = WS_CHILD | WS_VISIBLE | SS_CENTER;

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override
	{
		// create ship if it doesn't exist yet
		ShipPos = p;
		if (!ship){
			ship.create(*this, style1, "x", 0, p.x, p.y, ShipSize, ShipSize);
		}
		else  
			// change current location
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void on_key_up(int vk) override
	{
		// mark ship (if exists) as "not moving"
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
	}

	void on_key_down(int vk) override
	{
		// if ship exists, move it depending on key and mark as "moving"
		RECT window_border;
		GetClientRect(*this, &window_border);
		int ShipSpeed = GetAsyncKeyState(VK_CONTROL) ? 40 : 10;
		if (ship)
		{
			switch (vk)
			{
			case VK_UP:
				ShipPos.y = max(ShipPos.y - ShipSpeed, window_border.top);
				break;
			case VK_DOWN:
				ShipPos.y = min(ShipPos.y + ShipSpeed, window_border.bottom - ShipSize);
				break;
			case VK_LEFT:
				ShipPos.x = max(ShipPos.x - ShipSpeed, window_border.left);
				break;
			case VK_RIGHT:
				ShipPos.x = min(ShipPos.x + ShipSpeed, window_border.right - ShipSize);
				break;
			default:
				return;
			}

			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style |= WS_BORDER;

			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, ShipPos.x, ShipPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}

	void on_destroy() override
	{
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT ShipPos;
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}