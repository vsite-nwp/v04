#include "nwpwin.h"

class Static :public Window {
protected:
	std::string ClassName()override { return "Static"; }
};

class MainWindow : public Window
{
	Static shp;
	POINT cords;
	LPRECT wnd;
protected:
	void OnLButtonDown(POINT p) {
		if (!shp)
			shp.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		cords.x = p.x;
		cords.y = p.y;

		SetWindowPos(shp, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}


	}
	void OnKeyDown(int vk) {
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}

		switch (vk) {
		case VK_LEFT:
			SetWindowPos(shp, 0, GetAsyncKeyState(VK_CONTROL)?cords.x-=20:--cords.x, cords.y, 20,20,SWP_FRAMECHANGED);
			break;
		case VK_RIGHT:
			SetWindowPos(shp, 0, GetAsyncKeyState(VK_CONTROL) ? cords.x += 20 : ++cords.x, cords.y, 20, 20, SWP_FRAMECHANGED);
			break;
		case VK_DOWN:
			SetWindowPos(shp, 0, cords.x, GetAsyncKeyState(VK_CONTROL) ? cords.y += 20 : ++cords.y, 20, 20, SWP_FRAMECHANGED);
			break;
		}
		case VK_UP:
			SetWindowPos(shp, 0, cords.x, GetAsyncKeyState(VK_CONTROL) ? cords.y -= 20 : --cords.y, 20, 20, SWP_FRAMECHANGED);
		}
	}
	void OnDestroy() {
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