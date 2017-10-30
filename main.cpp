#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
class Static:public Window {
protected:
	std::string ClassName()override { return "Static"; }
};

class MainWindow : public Window
{
	Static shp;
protected:
	void OnLButtonDown(POINT p) {
		if (!shp)
			shp.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		SetWindowPos(shp, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", 0);
			return;
		}

		switch (vk) {
		case VK_LEFT:

			break;
		case VK_RIGHT:
			break;
		case VK_DOWN:
			break;
		case VK_UP:
			
		}
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
