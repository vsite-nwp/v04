#include "nwpwin.h"

class Static : public Window {public: std::string ClassName() override { return "STATIC"; }};
class MainWindow : public Window
{
	RECT sea;
	Static ship;
	POINT current_pos;
	int speed;
	bool isMoving;
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER , "x",0, p.x, p.y,20,20 );
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;	
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnKeyUp(int vk) 
	{
		isMoving = false;
		moving();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void OnKeyDown(int vk) {
		if (!ship)
			return;	
		GetClientRect(*this, &sea);
		GetKeyState(VK_CONTROL)<0 ? speed = 15 : speed = 5;
	// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		goUp(); goDown(); goLeft(); goRight();
		moving();	
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void goRight() { if (GetKeyState(VK_RIGHT) < 0 && current_pos.x < sea.right - 30) { current_pos.x += speed; isMoving = true; } }
	void goLeft() { if (GetKeyState(VK_LEFT) < 0 && current_pos.x > 0) { current_pos.x -= speed; isMoving = true; } }
	void goDown() { if (GetKeyState(VK_DOWN) < 0 && current_pos.y < sea.bottom - 30) { current_pos.y += speed; isMoving = true; } }
	void goUp()    { if (GetKeyState(VK_UP)    < 0 && current_pos.y > 25){current_pos.y -= speed; isMoving = true; } }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void moving() 
	{
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		isMoving ? SetWindowLong(ship, GWL_STYLE, style | WS_BORDER) : SetWindowLong(ship, GWL_STYLE, style& ~WS_BORDER);
		SetWindowPos(ship,0,current_pos.x,current_pos.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
