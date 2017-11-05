#include "nwpwin.h"

class Static :public Window {
protected:
	std::string ClassName()override { return "Static"; }
};

class MainWindow : public Window
{
	Static shp;
	POINT cords;
protected:
	void OnLButtonDown(POINT p) {
		if (!shp)
			shp.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);

		cords = p;

		SetWindowPos(shp, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}

		int style=GetWindowLong(shp, GWL_STYLE)&~WS_BORDER;

		SetWindowLong(shp, GWL_STYLE, style);
		SetWindowPos(shp, 0, cords.x, cords.y, 20, 20, SWP_FRAMECHANGED);
	}
	void OnKeyDown(int vk) {
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}

		int style = GetWindowLong(shp, GWL_STYLE)|WS_BORDER;

		RECT wnd;
		GetClientRect(*this, &wnd);
		int mov = GetAsyncKeyState(VK_CONTROL) ? 20 : 1;;

		switch (vk) {
		case VK_LEFT:
			cords.x = max(cords.x - mov, 0);
			break;
		case VK_RIGHT: {
			cords.x = min(cords.x + mov, wnd.right-20);
			break;
		}
		case VK_DOWN: {
			cords.y = min(cords.y + mov, wnd.bottom - 20);
			break;
		}
		case VK_UP:
			cords.y = max(cords.y - mov, 0);
			break;
		}

		SetWindowLong(shp, GWL_STYLE, style);
		SetWindowPos(shp, 0, cords.x, cords.y, 20, 20, SWP_FRAMECHANGED);
	}
	void OnDestroy() {
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