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

		RECT wnd;
		GetWindowRect(*this, &wnd);
		int mov = GetAsyncKeyState(VK_CONTROL) ? 20 : 1;;

		switch (vk) {
		case VK_LEFT:
			if (!cords.x)
				break;
			else if (cords.x < 20)
				mov = cords.x;

			SetWindowPos(shp, 0,cords.x-=mov, cords.y, 20,20,SWP_FRAMECHANGED);
			break;
		case VK_RIGHT: {
			int dif = wnd.right-cords.x-20;
			if (cords.x==wnd.right)
				break;
			else if (dif<20&&mov==20)
				mov = dif;

			SetWindowPos(shp, 0, cords.x += mov, cords.y, 20, 20, SWP_FRAMECHANGED);
			break;
		}
		case VK_DOWN: {
			int dif = wnd.bottom - cords.y-20;
			if (!dif)
				break;
			else if (dif < 20 && mov == 20)
				mov = dif;

			SetWindowPos(shp, 0, cords.x, cords.y += mov, 20, 20, SWP_FRAMECHANGED);
			break;
		}
		case VK_UP:
			if (!cords.y)
				break;
			else if (cords.y < 20)
				mov = cords.y;

			SetWindowPos(shp, 0, cords.x, cords.y-=mov, 20, 20, SWP_FRAMECHANGED);
		}
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