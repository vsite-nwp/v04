#include "nwpwin.h"

class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }
};

int const shipSize = 25;

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		pozicija = p;

		if (!ship)
			ship.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER, "x", 0, p.x, p.y, shipSize, shipSize);
		else
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void on_key_up(int vk) override {
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;

		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
	}
	void on_key_down(int vk) override {
		int Brzina = GetAsyncKeyState(VK_CONTROL) ? 60 : 30 ;

		if (ship)
		{
			RECT border;
			GetClientRect(*this, &border);

			switch (vk)
			{
			case VK_UP:
				pozicija.y = max(pozicija.y - Brzina, border.top);
				break;
			case VK_DOWN:
				pozicija.y = min(pozicija.y + Brzina, border.bottom - shipSize);
				break;
			case VK_LEFT:
				pozicija.x = max(pozicija.x - Brzina, border.left);
				break;
			case VK_RIGHT:
				pozicija.x = min(pozicija.x + Brzina, border.right - shipSize);
				break;
			default:
				return;
			}

			DWORD style = GetWindowLong(ship, GWL_STYLE);
			style |= WS_BORDER;

			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, pozicija.x, pozicija.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}

	void on_destroy() override {
		::PostQuitMessage(0);
	}

private:
	Static ship;
	POINT pozicija;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
