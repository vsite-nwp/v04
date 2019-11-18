

#include "nwpwin.h"

#define SIZEOFSHIP 30


class Static : public Window {
public:
	std::string ClassName() { return "static"; };
};
class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) {
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, SIZEOFSHIP, SIZEOFSHIP);
		}
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			int f = GetWindowLong(ship, GWL_STYLE);
			f &= WS_VISIBLE | WS_CHILD | SS_CENTER;
			SetWindowLong(ship, GWL_STYLE, f);
			SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	void OnKeyDown(int vk) {
		RECT frame;
		GetClientRect(*this, &frame);
		if (ship) {
			int f= GetWindowLong(ship, GWL_STYLE);
			f |= WS_BORDER;
			SetWindowLong(ship, GWL_STYLE, f);
			switch (vk) {
			case VK_LEFT:
				if (Fast())
					point.x -= 20;
				else
					point.x -= 5;
				if (point.x < frame.left)
					point.x = frame.left;
				MoveShip();
				break;
			case VK_RIGHT:
				if (Fast())
					point.x += 20;
				else
					point.x += 5;
				if (point.x > frame.right - SIZEOFSHIP)
					point.x = frame.right - SIZEOFSHIP;
				MoveShip();
				break;
			case VK_UP:
				if (Fast())
					point.y -= 20;
				else
					point.y -= 5;
				if (point.y < frame.top)
					point.y = frame.top;
				MoveShip();
				break;
			case VK_DOWN:
				if (Fast())
					point.y += 20;
				else
					point.y += 5;
				if (point.y > frame.bottom - SIZEOFSHIP)
					point.y = frame.bottom - SIZEOFSHIP;
				MoveShip();
				break;
			default:
				return;
			}
		}
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT point;
	boolean Fast() { return GetKeyState(VK_CONTROL) < 0; }
	void MoveShip()
	{
		SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}

