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
		if (!ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"

		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			switch (vk) {
			case VK_UP:
				point.y -= 5;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_DOWN:
				point.y += 5;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_LEFT:
				point.x -= 5;
				SetWindowPos(ship, 0, point.x, point.y, 0, 0,  SWP_NOSIZE | SWP_NOZORDER);
				break;
			case VK_RIGHT:
				point.x += 5;
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
