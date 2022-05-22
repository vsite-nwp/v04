#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship
class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }
};

int const shipSize = 20;
class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override {
		//create ship if it doesn't exist yet
		
		position = p;

		if (!ship)
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER, "X", 0, p.x, p.y, shipSize, shipSize);
		//change current location
	
		else
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	
	void on_key_up(int vk) override {
		//mark ship (if exists) as "not moving"
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;

		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
	}
	
	void on_key_down(int vk) override {
		//if ship exists, move it depending on key and mark as "moving"
		int shipSpeed = GetAsyncKeyState(VK_CONTROL) ? 30 : 15;
		

		

		if (ship)
		{
			RECT border;
			GetClientRect(*this, &border);
			
			switch (vk)
			{
			case VK_UP:
				position.y = max(position.y - shipSpeed, border.top);
				break;
			case VK_DOWN:
				position.y = min(position.y + shipSpeed, border.bottom - shipSize);
				break;
			case VK_LEFT:
				position.x = max(position.x - shipSpeed, border.left);
				break;
			case VK_RIGHT:
				position.x = min(position.x + shipSpeed, border.right - shipSize);
				break;
			default:
				return;
			}

			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style |= WS_BORDER;

			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}

private:
	Static ship;
	POINT position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}