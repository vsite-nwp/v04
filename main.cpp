#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
private:
	Static ship;
	POINT pos = {0, 0};
	const DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;

protected:
	void OnLButtonDown(POINT p) {
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
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}