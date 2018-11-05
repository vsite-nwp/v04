#define NOMINMAX
#include "nwpwin.h"
#include <algorithm>

class Static : public Window 
{
public:
	std::string ClassName() override { return "STATIC"; }
};

const SIZE ship_size = {30,20};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) 
			ship.Create(*this, style, "X", 0, p.x, p.y, ship_size.cx, ship_size.cy);
		else 
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);			
		position = p;
	}
	void OnKeyUp(int vk) {
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		bool ctrl = ::GetAsyncKeyState(VK_CONTROL);
		int speed = ctrl ? 5 : 1;

		RECT rect_this;
		GetWindowRect(*this, &rect_this);

		POINT upDown = { rect_this.top, rect_this.bottom };
		ScreenToClient(*this, &upDown);
		POINT leftRight = { rect_this.left, rect_this.right };
		ScreenToClient(*this, &leftRight);

		switch (vk) 
		{			
		case VK_UP:
			position.y = std::max(upDown.x, position.y - speed);
			break;
		case VK_DOWN:
			position.y = std::min(upDown.y -15, position.y + speed);
			break;
		case VK_LEFT:
			position.x = std::max(leftRight.x, position.x - speed);
			break;
		case VK_RIGHT:
			position.x = std::min(leftRight.y, position.x + speed);
			break;
		default:
			return;
		}

		SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
		SetWindowPos( ship, 0, position.x, position.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);				
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT position;
	const DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
