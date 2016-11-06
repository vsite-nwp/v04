#include "nwpwin.h"

#define S_SIZE = 20

 class Static : public Window {
 public:
	std::string ClassName() { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) { 
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE |SS_CENTER, "X", NULL, p.x, p.y, 15, 15);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SS_CENTER);
		point = p;
	}	

	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"

	}
	void OnKeyDown(int vk) {
		RECT frame;
		GetClientRect(*this, &frame);

		if (ship) {
			switch (vk) {
			case VK_UP:
				if (GetKeyState(VK_CONTROL) < 0)
					point.y -= 20;
				else
				point.y -= 5;
				if (point.y < frame.top)
					point.y = frame.top;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_DOWN:
				if (GetKeyState(VK_CONTROL) < 0)
					point.y += 20;
				else
				point.y += 5;
				if (point.y > frame.bottom - 15)
					point.y = frame.bottom - 15;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_LEFT:
				if (GetKeyState(VK_CONTROL) < 0)
					point.x -= 20;
				else
				point.x -= 5;
				if (point.x < frame.left)
					point.x = frame.left;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_RIGHT:
				if (GetKeyState(VK_CONTROL) < 0)
					point.x += 20;
				else
				point.x += 5;
				if (point.x > frame.right - 15)
					point.x = frame.right - 15;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER);
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
	void Move(POINT p) { SetWindowPos(ship, 0, p.x, p.y, NULL, NULL,NULL); }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
