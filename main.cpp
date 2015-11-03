#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
class Static : public Window{
public:
	std::string ClassName(){ 
		return "STATIC"; 
	}
};


class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		if (!ship){
			ship.Create(*this, WS_CHILD | WS_VISIBLE , "X", 0, (int)p.x, (int)p.y, 20, 20);
		}
		// TODO: change current location
	
		SetWindowPos(ship, 0, (int)p.x, (int)p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
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
	POINT current_position;


};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
