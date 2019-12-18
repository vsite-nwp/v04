#include "nwpwin.h"
#define BASIC 2;

class Ship : public Window {
protected:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		static int cntr = 0;
		if (!cntr)
		{
			shp.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, 20, 20);
			++cntr;
		}
	
		else
			SetWindowPos(GetWindow(*this,GW_CHILD), HWND_TOP, p.x, p.y, 1, 1, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		if (vk == VK_CONTROL)
			speed = BASIC;
		SetWindowLong((HWND)shp, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos((HWND)shp, HWND_TOP, 1, 1, 1, 1, SWP_FRAMECHANGED | SWP_NOMOVE| SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		if (vk == VK_CONTROL)
			speed = 10 * BASIC;
		GetClientRect(*this, &rctClient);
		if (GetWindowRect((HWND)shp, &rctShip))
		{
			p.x = rctShip.left; p.y = rctShip.top;
			ScreenToClient(*this, &p);
			SetWindowLong((HWND)shp, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			switch (vk)
			{
				case VK_LEFT:	if (p.x - speed > rctClient.left) p.x -= speed;	break;
				case VK_UP:		if (p.y - speed > rctClient.top) p.y -= speed;	break;
				case VK_RIGHT:	if (p.x + speed < rctClient.right - 20) p.x += speed;	break;
				case VK_DOWN:	if (p.y + speed < rctClient.bottom - 20) p.y += speed;	break;
			}
			SetWindowPos((HWND)shp, HWND_TOP, p.x, p.y, 1, 1, SWP_FRAMECHANGED|SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Ship shp;
	POINT p;
	int speed = BASIC;
	RECT rctShip, rctClient;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
