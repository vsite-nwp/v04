#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() override{return "STATIC";}
};

class MainWindow : public Window
{

protected:
	void OnLButtonDown(POINT p) {
		if(!ship)
			ship.Create(*this,WS_CHILD  | WS_VISIBLE| SS_CENTER, "o", 0, p.x, p.y, 20, 20);
		current_style = GetWindowLong(ship, GWL_STYLE);
		SetWindowPos(ship,0,p.x,p.y,0,0, SWP_NOSIZE | SWP_NOZORDER);
		curent_pos = p;
			
	}
	void OnKeyUp(int vk) {
		::SetWindowLong(ship, GWL_STYLE, current_style );
		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		int ctrl = GetAsyncKeyState(VK_CONTROL);

		unsigned turbo = 4;
		unsigned normal = 1;

		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_UP: 
			curent_pos.y -= (ctrl ?  turbo : normal);
			curent_pos.y < 0 ? curent_pos.y = 0 : 0;
			break;
		case VK_DOWN: 
			curent_pos.y += (ctrl ? turbo : normal);
			curent_pos.y > rect.bottom-20 ? curent_pos.y = rect.bottom-20 : 0;
			break;
		case VK_LEFT: 
			curent_pos.x -= (ctrl ? turbo : normal);
			curent_pos.x < 0 ? curent_pos.x = 0 : 0;
			break;
		case VK_RIGHT: 
			curent_pos.x += (ctrl ? turbo : normal);
			curent_pos.x > rect.right - 20 ? curent_pos.x = rect.right - 20 : 0;
			break;
		default :
			return;
		}

		::SetWindowLong(ship, GWL_STYLE, current_style | WS_BORDER);
		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_FRAMECHANGED  | SWP_NOSIZE | SWP_NOZORDER );
		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT curent_pos;
	DWORD current_style;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
