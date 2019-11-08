#include "nwpwin.h"

#define SIZEOFSHIP 20
#define SLOW 5
#define FAST 20

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
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
		point = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			int focus = GetWindowLong(ship, GWL_STYLE);
			focus &= WS_VISIBLE | WS_CHILD | SS_CENTER;
			SetWindowLong(ship, GWL_STYLE, focus);
			SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	void OnKeyDown(int vk) {
		RECT frame;
		GetClientRect(*this, &frame);
		if (ship) {
			int focus = GetWindowLong(ship, GWL_STYLE);
			focus |= WS_BORDER;
			SetWindowLong(ship, GWL_STYLE, focus);
			switch (vk) {
			case VK_LEFT:
				if (Faster())
					point.x -= FAST;
				else
					point.x -= SLOW;
				if (point.x < frame.left)
					point.x = frame.left;
				MoveShip();				
				break;
			case VK_RIGHT:
				if (Faster())
					point.x += FAST;
				else
					point.x += SLOW;
				if (point.x > frame.right - SIZEOFSHIP)
					point.x = frame.right - SIZEOFSHIP;
				MoveShip();				
				break;
			case VK_UP:
				if (Faster())
					point.y -= FAST;
				else
					point.y -= SLOW;
				if (point.y < frame.top)
					point.y = frame.top;
				MoveShip();				
				break;
			case VK_DOWN:
				if (Faster())
					point.y += FAST;
				else
					point.y += SLOW;
				if (point.y > frame.bottom - SIZEOFSHIP)
					point.y = frame.bottom - SIZEOFSHIP;
				MoveShip();
				break;
			default:
				return;
			}
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT point;
	boolean Faster() { return GetKeyState(VK_CONTROL) < 0; }
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
