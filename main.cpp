#include "nwpwin.h"

#define SIZEOFSHIP 20

class Static : public Window {
public:
	std::string ClassName() { return "static"; };
};
class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship) {
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, SIZEOFSHIP, SIZEOFSHIP);
		}
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SS_CENTER);
		point = p;
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
	POINT point;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
