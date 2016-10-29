#include "nwpwin.h"

// TODO: prepare class (Static) for a ship

 class Static : public Window {
 public:
	std::string ClassName() { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) { 
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE, "x", NULL, (int)p.x, (int)p.y, 15, 15);

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
	Static ship;
	void Move(POINT p) { SetWindowPos(ship, 0, p.x, p.y, NULL, NULL,NULL); }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
