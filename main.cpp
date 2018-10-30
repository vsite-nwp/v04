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
		if(!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0 ,p.x, p.y, ship_size.cx,ship_size.cy);
		else 
		{
			DestroyWindow(ship);
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, ship_size.cx, ship_size.cy);
		}
	}
	void OnKeyUp(int vk) {
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos(ship, 0, 0, 0, 0, 0,
			SWP_SHOWWINDOW | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		bool ctrl = ::GetAsyncKeyState(VK_CONTROL);
		int speed = ctrl ? 5 : 1;


		RECT rect_ship;		
		GetWindowRect(ship, &rect_ship);
		POINT position = { rect_ship.left, rect_ship.top };
		
		RECT rect_this;
		GetWindowRect(*this, &rect_this);

		switch (vk) 
		{			
		case VK_UP:
			if(rect_this.top + 30 <position.y)
				position.y -= speed;
			break;
		case VK_DOWN:
			if (rect_this.bottom - 30 > position.y)
				position.y += speed;
			break;
		case VK_LEFT:
			if(rect_this.left <position.x)
				position.x -= speed;
			break;
		case VK_RIGHT:
			if (rect_this.right - 30 > position.x)
				position.x += speed;
			break;
		}
		ScreenToClient(*this, &position);
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos( ship, 0, position.x, position.y, 0, 0, 
			SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);
		
		
		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
