#include "nwpwin.h"

class Static : public Window {
	std::string ClassName() override { return "Static"; };
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this,WS_CHILD|WS_VISIBLE|SS_CENTER,"X",p.x, p.y,20,20);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE|SWP_NOZORDER | SS_CENTER);
		currentP = p;
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		// VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT currentP;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
