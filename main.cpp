#include "nwpwin.h"
#define SHIP_WIDTH 20
#define SHIP_HEIGHT 20  //size of ship in pixels

// TODO: prepare class (Static) for a ship
class Static : public Window {

public:
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
protected:
	Static ship;
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		if (!ship) {

			ship.Create(*this, WS_VISIBLE | WS_CHILD, "x", NULL, p.x, p.y, SHIP_WIDTH, SHIP_HEIGHT);
		}

		// TODO: change current location
		SetWindowPos(ship,NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	}
	void OnKeyUp(int vk) {
		
		// TODO: mark ship (if exists) as "not moving"
		
	}
	void OnKeyDown(int vk) {
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
