#include "nwpwin.h"
using namespace std;

// TODO: prepare class (Static) for a ship
class Static : public Window {
	string ClassName() override { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT cur_pos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st) {
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x",0, p.x, p.y, 20, 20);
		}
		SetWindowPos(st,0,p.x,p.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		cur_pos = p;
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
