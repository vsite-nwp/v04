#include "nwpwin.h"
#define SHIP_WIDTH 16
#define SHIP_HEIGHT 25  //size of ship in pixels

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
	
		// TODO: change current location
		

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
