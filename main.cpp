#include "nwpwin.h"
#include "math.h"

// TODO: prepare class (Static) for a ship
class Static:public Window{
	std::string ClassName() override { return "STATIC"; }
	
};

class MainWindow : public Window
{
	Static st;
	POINT current_pos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
	}
	void OnKeyUp(int vk)
	{
		if (st)
		{
			SetWindowLong(st, GWL_EXSTYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void position_change(int x, int y)
	{
		RECT right_wall;
		GetClientRect(*this, &right_wall);
		if (current_pos.x < abs(x) && x < 0)
		{
			current_pos.x = 0;
		}
		else if (current_pos.x > right_wall.right - 20 - x)
		{
			current_pos.x = right_wall.right - 20;
		}
		else
		{
			current_pos.x += x;
		}
		RECT floor;
		GetClientRect(*this, &floor);
		if (current_pos.y < abs(y) && y < 0)
		{
			current_pos.y = 0;
		}
		else if(current_pos.y>floor.bottom-20-y)
		{
			current_pos.y = floor.bottom - 20;
		}
		else
		{
			current_pos.y += y;
		}
		SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		SetWindowLong(st, GWL_EXSTYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		int x=0, y=0;
		switch (vk) {
		case VK_LEFT:
			x = -10;
			break;
		case VK_RIGHT:
			x = 10;
			break;
		case VK_DOWN:
			y = 10;
			break;
		case VK_UP:
			y = -10;
			break;
		}
		if (GetKeyState(VK_CONTROL) & 0x8000)
			x *= 5, y *= 5;
		position_change(x, y);
		// TODO: if ship exists, move it depending on key and mark as "moving"
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
