#include "nwpwin.h"


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
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, ship_size.cx, ship_size.cy);
			style = GetWindowLong(ship, GWL_STYLE);
		}
		else 
		{
			SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);			
		}
		position = {p.x,p.y};
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

		switch (vk) 
		{			
		case VK_UP:
			position.y = max(rect_this.top, position.y - speed);
			break;
		case VK_DOWN:
			position.y = min(rect_this.bottom - 40, position.y + speed);
			break;
		case VK_LEFT:
			position.x = max(rect_this.left, position.x - speed);
			break;
		case VK_RIGHT:
			position.x = min(rect_this.right - 40, position.x + speed);
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
	DWORD style;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
