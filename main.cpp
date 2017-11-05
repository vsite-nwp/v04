#include "nwpwin.h"

class Static : public Window{
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT currPos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE, ";)", NULL, p.x, p.y, 20, 20);
		SetWindowPos(st, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		currPos = p;
	};
		// TODO: change current location
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