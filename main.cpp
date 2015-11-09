#include "nwpwin.h"
#define SHIP_ID 1

// TODO: prepare class (Static) for a ship

class Static : public Window
{
	std::string ClassName(){ return "static"; }
};

class MainWindow : public Window
{
public:
	Static s;
	POINT cp;
	RECT rect;
	bool ctrlPritisnut = false;
protected:
	void OnLButtonDown(POINT p) {
		if (!s)
		{
			GetClientRect(*this, &rect);
			s.Create(*this, WS_CHILD | WS_VISIBLE, "X", SHIP_ID, p.x, p.y, 15, 20);
			rect.bottom -= 20;
			rect.right -= 15;
			cp = p;
		}
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
