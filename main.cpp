#include "nwpwin.h"


// TODO: prepare class (Static) for a ship
class Static : public Window {

public:
	std::string ClassName() override { return "STATIC"; }

};

class MainWindow : public Window
	{

	Static ship;
	POINT current_pos;

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
		not_moving();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void OnKeyDown(int vk) {
		if (!ship)
			return;	
		RECT sea;
		GetClientRect(*this, &sea);
		

		int speed;
		GetKeyState(VK_CONTROL)<0 ? speed = 15 : speed = 5;
	// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//Up left
		if ((GetKeyState(VK_UP)<0)&&(GetKeyState(VK_LEFT)<0)&&current_pos.x>5&&current_pos.y>25)
		{
			current_pos.y -= speed;
			current_pos.x -= speed;
		}
		//Up right
		else if((GetKeyState(VK_UP)<0)&&(GetKeyState(VK_RIGHT)<0)&&current_pos.x<sea.right-25&&current_pos.y>25)
		{
			current_pos.y -= speed;
			current_pos.x += speed;
		}
		//Down left
		else if((GetKeyState(VK_DOWN)<0)&&(GetKeyState(VK_LEFT)<0)&&current_pos.y<sea.bottom-25&&current_pos.x>5)
		{
			current_pos.y += speed;
			current_pos.x -= speed;
		}
		//Down right
		else if((GetKeyState(VK_DOWN)<0)&&(GetKeyState(VK_RIGHT)<0&&current_pos.y<sea.bottom-25&&current_pos.x<sea.right-25))
		{
			current_pos.y += speed;
			current_pos.x += speed;
		}

		else if (vk==VK_UP&&current_pos.y>25)
			current_pos.y -= speed;
		else if (vk==VK_DOWN&&current_pos.y<sea.bottom-25)
			current_pos.y += speed;
		else if (vk==VK_LEFT&&current_pos.x>25)
			current_pos.x -= speed;
		else if (vk==VK_RIGHT&&current_pos.x<sea.right-25)
			current_pos.x += speed;
		
		moving();	
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void moving() 
	{
		SetWindowLong(ship,GWL_STYLE,GetWindowLong(ship ,GWL_STYLE)| WS_BORDER);
		SetWindowPos(ship,0,current_pos.x,current_pos.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
	}
	void not_moving()
	{
		SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE) & ~ WS_BORDER);
		SetWindowPos(ship,0,current_pos.x,current_pos.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOMOVE|SWP_FRAMECHANGED);
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
