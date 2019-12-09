#include "nwpwin.h"

class Static : public Window
{
	public:
		std::string	ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		position = p;
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, position.x, position.y, 45, 45);

		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		
		position = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			int SailSpeed = 5;
			if (GetKeyState(VK_CONTROL) < 0)
				SailSpeed += 30;
			RECT ship_rectangle;
			GetClientRect(*this, &ship_rectangle);
			switch (vk) {
			case VK_UP:
				position.y = max(ship_rectangle.top, position.y - SailSpeed);
				break;
			case VK_DOWN:
				position.y = min(ship_rectangle.bottom - 20, position.y + SailSpeed);
				break;
			case VK_LEFT:
				position.x = max(ship_rectangle.left, position.x - SailSpeed);
				break;
			case VK_RIGHT:
				position.x = min(ship_rectangle.right - 20, position.x + SailSpeed);
				break;
			default:return;

			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);

		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
