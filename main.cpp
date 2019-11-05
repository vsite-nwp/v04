#include "nwpwin.h"

#define SIZEOFSHIP 20
#define SLOW 5
#define FAST 15

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
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SS_CENTER);
		point = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			switch (vk) {
			case VK_LEFT:
				if (GetKeyState(VK_CONTROL) < 0)
					point.x -= FAST;
				else
					point.x -= SLOW;
				SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				break;
			case VK_RIGHT:
				if (GetKeyState(VK_CONTROL) < 0)
					point.x += FAST;
				else
					point.x += SLOW;
				SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				break;
			case VK_UP:
				if (GetKeyState(VK_CONTROL) < 0)
					point.y -= FAST;
				else
					point.y -= SLOW;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				break;
			case VK_DOWN:
				if (GetKeyState(VK_CONTROL) < 0)
					point.y += FAST;
				else
					point.y += SLOW;
				SetWindowPos(ship, NULL, point.x, point.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				break;
			default:
				return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT point;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
