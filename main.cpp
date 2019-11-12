#include "nwpwin.h"
#define SHIPSIZE 20
#define SLOW 10
#define FAST 30
#define BSTYLE (WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER)

class Static : public Window
{
public:
	std::string ClassName() 
	{ 
		return "STATIC"; 
	}
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {

		if (!Ship)
		{
		Ship.Create(*this, BSTYLE & ~WS_BORDER, "x", 0, p.x, p.y, SHIPSIZE, SHIPSIZE);
		}
		SetWindowPos(Ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void OnKeyUp(int vk) {
		if (Ship) {
			SetWindowLong(Ship, GWL_STYLE, BSTYLE & ~WS_BORDER);
			SetWindowPos(Ship, 0, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if(Ship)
		{
			RECT sea;
			GetClientRect(*this, &sea);
			int move = GetAsyncKeyState(VK_CONTROL) ? FAST : SLOW;
			switch(vk)
			{
				case VK_DOWN:
					position.y = min(sea.bottom - SHIPSIZE, position.y + move);
					break;
				case VK_UP:
					position.y = max(sea.top, position.y - move);
					break;
				case VK_RIGHT:
					position.x = min(sea.right - SHIPSIZE, position.x + move);
					break;
				case VK_LEFT:
					position.x = max(sea.left, position.x - move);
					break;
				default:
					return;
			}
			SetWindowLong(Ship, GWL_STYLE, BSTYLE);
			SetWindowPos(Ship, 0, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static Ship;
	POINT position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}