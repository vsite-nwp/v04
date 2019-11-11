#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() override{
		return "STATIC";
	}
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		pozicija = p;
		if (!ship) {
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, pozicija.x, pozicija.y, 30, 30);
		}
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pozicija = p;
	}
	void OnKeyUp(int vk) {
		if (ship){
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, pozicija.x, pozicija.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			int MoveSpeed = 5;
			if (GetKeyState(VK_CONTROL) < 0)
				MoveSpeed += 30;
			RECT ship_r;
			GetClientRect(*this, &ship_r);
			switch (vk) {
			case VK_UP:
				pozicija.y = max(ship_r.top, pozicija.y - MoveSpeed);
				break;
			case VK_DOWN:
				pozicija.y = min(ship_r.bottom - 20, pozicija.y + MoveSpeed);
				break;
			case VK_LEFT:
				pozicija.x = max(ship_r.left, pozicija.x - MoveSpeed);
				break;
			case VK_RIGHT:
				pozicija.x = min(ship_r.right - 20, pozicija.x + MoveSpeed);
				break;
			default: return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, 0, pozicija.x, pozicija.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT pozicija;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
