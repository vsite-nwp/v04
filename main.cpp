#include "nwpwin.h"

class Static : public vsite::nwp::window {
	std::string class_name() { return "Static"; }
};

const int sizeX = 20;
const int sizeY = 20;

class main_window : public vsite::nwp::window
{
	Static st;
	POINT currPos;
	LONG style;

protected:
	void on_left_button_down(POINT p) {
		if (!st)
			st.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, ":)", NULL, p.x, p.y, sizeX, sizeY);
		currPos = p;
		naCrtajMe(false);
	};

	void on_key_up(int vk) {
		if (st) {
			naCrtajMe(false);
		}
	}
	void on_key_down(int vk) {
		if (st)
		{
			int Speed = 5;
			if (GetKeyState(VK_LCONTROL) < 0)
				Speed = 20;

			RECT stPosition;
			GetClientRect(*this, &stPosition);

			switch (vk) {
			case (VK_LEFT):
				currPos.x = max(0, currPos.x - Speed);
				break;
			case (VK_RIGHT):
				currPos.x = min(stPosition.right - sizeX, currPos.x + Speed);
				break;
			case (VK_UP):
				currPos.y = max(0, currPos.y - Speed);
				break;
			case(VK_DOWN):
				currPos.y = min(stPosition.bottom - sizeY, currPos.y + Speed);
				break;
			default:
				return;
			}
			naCrtajMe(true);
		}
	}
	void naCrtajMe(bool haveBorder) {
		DWORD current_style = GetWindowLong(st, GWL_STYLE);
		current_style = haveBorder ? (current_style | WS_BORDER) : (current_style & ~WS_BORDER);
		SetWindowLong(st, GWL_STYLE, current_style);
		SetWindowPos(st, NULL, currPos.x, currPos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

	void on_destroy() {
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}