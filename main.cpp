#include "nwpwin.h"

class Static :public Window {
public:
	std::string ClassName() {

		return "Static";
	}
	
};

class MainWindow : public Window
{
	Static ship;
	POINT current_position;
protected:
	void OnLButtonDown(POINT p) {
	
		if (!ship) 
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, ("x"), NULL, NULL, NULL, 20, 20);

		
			
			current_position = p;
			Not_Move();
		}
	}
	void OnKeyUp(int vk) {
	
		if (ship) 
		{
			Mark_ship(false);
			
		}
	}
	void OnKeyDown(int vk) {
	
		if (ship)
		{
			int step=5;
			if (GetKeyState(VK_CONTROL) < 0) step = 10;
			RECT rc; ::GetClientRect(*this, &rc);
			if (vk == VK_LEFT )
				current_position.x = max(0,current_position.x - step);
			else if (vk == VK_RIGHT)
				current_position.x = min(rc.right-20, current_position.x + step);
			else if (vk == VK_UP)
				current_position.y = max(0, current_position.y - step);
			else if (vk == VK_DOWN)
				current_position.y = min(rc.bottom-20,current_position.y + step);
			else
				return;

			Mark_ship(true);
			Not_Move();
		}
		

		

	}	
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	void Not_Move() {
		::SetWindowPos(ship, HWND_BOTTOM, current_position.x, current_position.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	
 void Mark_ship(bool on) {
			DWORD style =GetWindowLong(ship, GWL_STYLE);
			style = on ? (style | WS_BORDER) : (style & ~WS_BORDER);
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, NULL, NULL, NULL, NULL, NULL,
				SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED); //border
		}


	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
