#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		current_position = p;
		if (!ship) {
			ship.Create(*this, WS_VISIBLE | WS_CHILD | SS_CENTER, "Ship",1,p.x,p.y,20,20);
		}
		else SetWindowPos(HWND(ship), HWND_TOP, p.x, p.y, 10, 10, NULL);
		
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		bool ctrl = ::GetAsyncKeyState(VK_CONTROL);
		RECT rc; ::GetClientRect(*this, &rc);
		switch (vk)
		{

		}
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
