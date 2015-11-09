#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
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
		// TODO: create ship if it doesn't exist yet
		if (!ship) 
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, ("x"), 0, 0, 0, 20, 20);

			// TODO: change current location
			
			current_position = p;
			Not_Move();
		}
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (ship) 
		{
			Mark_ship(false);
			
		}
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		
		



	}	
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	void Not_Move() {
		::SetWindowPos(ship, HWND_BOTTOM, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	
 void Mark_ship(bool on) {
			DWORD style = ::GetWindowLong(ship, GWL_STYLE);
			style = on ? (style | WS_BORDER) : (style & ~WS_BORDER);
			::SetWindowLong(ship, GWL_STYLE, style);
			::SetWindowPos(ship, 0, 0, 0, 0, 0,
				SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED); // border
		}


	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
