#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() 
	{ 
		return "STATIC"; 
	};
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		location = p;
		if (!ship) 
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, location.x, location.y, 30, 30);
		}
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		location = p;
	}
	void OnKeyUp(int vk) {
		if (ship)
		{
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, location.x, location.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			int moveSpeed = 10;
			if (GetKeyState(VK_CONTROL) < 0)
				moveSpeed += 10;
			RECT ship_r;
			GetClientRect(*this, &ship_r);

			switch (vk) {
			case VK_LEFT:
				location.x = max(ship_r.left, location.x - moveSpeed);
				break;
			case VK_RIGHT:
				location.x = min(ship_r.right - 20, location.x + moveSpeed);
				break;
			case VK_UP:
				location.y = max(ship_r.top, location.y - moveSpeed);
				break;
			case VK_DOWN:
				location.y = min(ship_r.bottom - 20, location.y + moveSpeed);
				break;
			default: 
				return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_BORDER | WS_VISIBLE);
			SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT location;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
