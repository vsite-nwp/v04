#define NOMINMAX
#include "nwpwin.h"
#include <algorithm>

class Static : public Window {
public:
	std::string ClassName() override{return "STATIC";}
};

class MainWindow : public Window
{

protected:
	void OnLButtonDown(POINT p) {
		if(!ship)
			ship.Create(*this, current_style, "o", 0, p.x, p.y, 20, 20);
		SetWindowPos(ship,0,p.x,p.y,0,0, SWP_NOSIZE | SWP_NOZORDER);
		curent_pos = p;
			
	}
	void OnKeyUp(int vk) {
		::SetWindowLong(ship, GWL_STYLE, current_style );
		SetWindowPos(ship, 0, curent_pos.x, curent_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		const int step = GetAsyncKeyState(VK_CONTROL) ? 4 : 1;

		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_UP: 
			curent_pos.y = std::max(curent_pos.y - step, rect.top);
			break;
		case VK_DOWN: 
			curent_pos.y = std::min(curent_pos.y + step, rect.bottom-20);
			break;
		case VK_LEFT: 
			curent_pos.x = std::max(curent_pos.x - step, rect.left);
			break;
		case VK_RIGHT: 
			curent_pos.x = std::min(curent_pos.x + step, rect.right - 20);
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
	const DWORD current_style = WS_CHILD | WS_VISIBLE | SS_CENTER;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
