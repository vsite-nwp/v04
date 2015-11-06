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
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, ("x"),0,0,0,20,20);

		// TODO: change current location
		SetWindowPos(ship,0,current_position.x,current_position.y,0,0,SWP_NOSIZE | SWP_NOZORDER);
		current_position = p;
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
