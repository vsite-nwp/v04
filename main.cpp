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
		GetClientRect(*this, &screen);
		shipPos = p;
		if (!ship)
			ship.Create(*this, style, "X", NULL, shipPos.x, shipPos.y, S_SIZE, S_SIZE);
			SetWindowPos(ship, NULL, shipPos.x, shipPos.y, 0, 0, UFLAGS);
			SetWindowLong(ship, GWL_STYLE, style);
	}
	void OnKeyUp(int vk) {
		if (ship){
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, NULL, 0, 0, 0, 0, UFLAGS | SWP_NOMOVE);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {
			int speed;
			if (GetKeyState(VK_CONTROL) < 0) speed = FAST;
			else speed = SLOW;
			switch (vk) {
				case VK_UP:shipPos.y= max(0, shipPos.y - speed); break;
				case VK_DOWN:shipPos.y = min(screen.bottom- S_SIZE, shipPos.y + speed); break;
				case VK_LEFT:shipPos.x = max(0, shipPos.x - speed); break;
				case VK_RIGHT:shipPos.x = min(screen.right - S_SIZE, shipPos.x + speed); break;
				defalt: break;
			}
			SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
			SetWindowPos(ship, NULL, shipPos.x, shipPos.y, 0, 0, UFLAGS);
			
		
		
		}
		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT shipPos;
	RECT screen;
	DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;
	UINT UFLAGS = SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
