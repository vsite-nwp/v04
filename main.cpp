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
		SetWindowPos(ship,0,p.x,p.y,0,0, SWP_NOSIZE | SWP_NOZORDER);
		curent_pos = p;
			
	}
	void OnKeyUp(int vk) {
		::SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER );
		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		int ctrl = GetAsyncKeyState(VK_CONTROL);

		switch (vk)
		{
		case VK_UP: 
			ctrl ? curent_pos.y -= 4 : curent_pos.y -= 1;
			break;
		case VK_DOWN: 
			ctrl ? curent_pos.y += 4 : curent_pos.y += 1;
			break;
		case VK_LEFT: 
			ctrl ? curent_pos.x -= 4 : curent_pos.x -= 1;
			break;
		case VK_RIGHT: 
			ctrl?curent_pos.x += 4:curent_pos.x += 1;
			break;
		}

		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		DWORD current_style = ::GetWindowLong(ship, GWL_STYLE);
		::SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );

		GetClientRect(*this, &rect);

		if (curent_pos.x > rect.right-20)
			curent_pos.x = rect.right-20;
		else if (curent_pos.x < rect.left)
			curent_pos.x = rect.left;
		else if (curent_pos.y < rect.top)
			curent_pos.y = rect.top;
		else if (curent_pos.y > rect.bottom-20)
			curent_pos.y = rect.bottom-20;
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT curent_pos;
	RECT rect;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
