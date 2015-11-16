#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
	Static ship;
	POINT position;
protected:
	void OnLButtonDown(POINT p) {
		position = p;
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "X", NULL, position.x, position.y, 15, 20);
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void OnKeyUp(int vk) {
		if (ship){
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		int gasPedal = 10;
		if (GetKeyState(VK_CONTROL) < 0)
			gasPedal = 50;
		RECT rekt;
		GetClientRect(*this, &rekt);
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
		switch (vk){
			case VK_UP:
				position.y = max(rekt.top, position.y - gasPedal);
				break;
			case VK_DOWN:
				position.y = min(rekt.bottom - 15, position.y + gasPedal);
				break;
			case VK_LEFT:
				position.x = max(rekt.left, position.x - gasPedal);
				break;
			case VK_RIGHT:
				position.x = min(rekt.right - 10 , position.x + gasPedal);
				break;
			default:
				return;
		}
		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		OnKeyUp(vk);
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
