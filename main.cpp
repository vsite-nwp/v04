#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
	Static ship;
	POINT position;
protected:
	void OnLButtonDown(POINT p) {
		position = p;
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "X", NULL, position.x, position.y, 15, 20);
		// TODO: change current location
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void OnKeyUp(int vk) {
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
		SetWindowPos(ship, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
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
