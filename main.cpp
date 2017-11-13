#include "nwpwin.h"

#define S_SIZE 20
#define SLOW 5
#define FAST 20

class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		
		shipPos = p;
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, shipPos.x, shipPos.y, S_SIZE, S_SIZE);
			SetWindowPos(ship, NULL, shipPos.x, shipPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE));
	}
	void OnKeyUp(int vk) {
		if (ship){
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE)  & !WS_BORDER);
			SetWindowPos(ship, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE);
		}
	}
	void OnKeyDown(int vk) {
		RECT screen;
		GetClientRect(*this, &screen);
		if (ship) {
			int speed;
			(GetKeyState(VK_CONTROL) < 0) ? speed = FAST : speed= SLOW;
			switch (vk) {
				case VK_UP:shipPos.y= max(0, shipPos.y - speed); break;
				case VK_DOWN:shipPos.y = min(screen.bottom- S_SIZE, shipPos.y + speed); break;
				case VK_LEFT:shipPos.x = max(0, shipPos.x - speed); break;
				case VK_RIGHT:shipPos.x = min(screen.right - S_SIZE, shipPos.x + speed); break;
				defalt:
			}
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE) | WS_BORDER);
			SetWindowPos(ship, NULL, shipPos.x, shipPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT shipPos;
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
