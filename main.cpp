#include "nwpwin.h"

class Static : public Window {
	std::string ClassName() override { return "Static"; };
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, 20, 20);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		currentP = p;
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			RECT glavniP;
			GetClientRect(*this, &glavniP);
			int brzina = 2;
			if (GetKeyState(VK_CONTROL) < 0)
				brzina = 10;
			switch (vk)
			{
			case VK_LEFT:
				currentP.x = max(glavniP.left, currentP.x - brzina);
				break;
			case VK_RIGHT:
				currentP.x = min(glavniP.right - 20,currentP.x+brzina);
				break;
			case VK_UP:
				currentP.y = max(glavniP.top, currentP.y - brzina);
				break;
			case VK_DOWN:
				currentP.y = min(glavniP.bottom - 20, currentP.y + brzina);
				break;
			default:
				return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(ship, 0, currentP.x, currentP.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT currentP;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
