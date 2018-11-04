#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};
const SIZE ship_size = { 30,20 };
class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		this->current_position = p;
		if(!ship)
			ship.Create(*this, WS_CHILD|WS_VISIBLE|SS_CENTER, "X", 0,p.x,p.y,ship_size.cx, ship_size.cy);
		else
		{
			::SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyUp(int vk) {
		if (ship) {
			DWORD current_style = ::GetWindowLong(ship, GWL_STYLE);
			::SetWindowLong(ship, GWL_STYLE, current_style | WS_BORDER);
			::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED| SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (!ship) return;
		bool ctrl = ::GetAsyncKeyState(VK_CONTROL);
		RECT rc;
		::GetClientRect(*this, &rc);
		int brzina;
		if (ctrl)
			brzina = 10;
		else
			brzina = 2;

		switch (vk)
		{

		case VK_UP:
			current_position.y = max(current_position.y - brzina, rc.top);
			break;

		case VK_DOWN:
			current_position.y = min(current_position.y + brzina, rc.bottom - ship_size.cy);
			break;

		case VK_LEFT:
			current_position.x = max(current_position.x - brzina, rc.left);
			break;

		case VK_RIGHT:
			current_position.x = min(current_position.x + brzina, rc.right - ship_size.cx);
			break;

		default: return;
		}

			DWORD current_style = ::GetWindowLong(ship, GWL_STYLE);
			::SetWindowLong(ship, GWL_STYLE, current_style|WS_BORDER ); 
		::SetWindowPos(ship, 0, current_position.x, current_position.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
				
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
