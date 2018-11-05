#include "nwpwin.h"

class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
			current_position = p;
			if (!ship) {
				ship.Create(*this, WS_VISIBLE | WS_CHILD | SS_CENTER, "X",1,p.x,p.y,20,20);
			}
			else SetWindowPos(ship, HWND_TOP, p.x, p.y, 20, 20, NULL);
		
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship,GWL_STYLE) & ~WS_BORDER);
			SetWindowPos(ship, NULL, NULL, NULL, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			bool ctrl = ::GetAsyncKeyState(VK_CONTROL);
			RECT rc; ::GetClientRect(*this, &rc);
			int speed = ctrl ? 20 : 10;
			switch (vk)
			{
			case VK_UP:
				current_position.y = max(current_position.y - speed, 0);
				break;
			case VK_DOWN:
				current_position.y = min(current_position.y + speed, rc.bottom - 20);
				break;
			case VK_LEFT:
				current_position.x = max(current_position.x - speed, 0);
				break;
			case VK_RIGHT:
				current_position.x = min(current_position.x + speed, rc.right - 20);
				break;
			}
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE) | WS_BORDER);
			SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
