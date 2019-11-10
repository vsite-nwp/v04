#include "nwpwin.h"

class Static :public Window {
	std::string ClassName()override
	{
		return "static";
	}

};
class MainWindow : public Window
{
	Static shippy;
	POINT po;
	RECT size;
	int step = 3;
	bool movestatus;
	void setStatus(bool isMoving) {
		if (isMoving)
		{
			SetWindowLong(shippy, GWL_STYLE, GetWindowLong(shippy, GWL_STYLE) | WS_BORDER);
		}
		else
		{
			SetWindowLong(shippy, GWL_STYLE, GetWindowLong(shippy, GWL_STYLE) & ~WS_BORDER);
		}
	}
	void teleport() {
		setStatus(movestatus);
		SetWindowPos(shippy, 0, po.x, po.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	bool checkForOutside(POINT coords, RECT size) {
		if (coords.x >= size.right - 20 || coords.y >= size.bottom - 20 || coords.x <= size.left || coords.y <= size.top) {
			return false;
		}
		return true;
	}
protected:
	void OnLButtonDown(POINT p) {
		GetClientRect(*this, &size);
		po.x = p.x;
		po.y = p.y;
		if (checkForOutside(p, size)) {
			if (!shippy)
			{
				shippy.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, 20, 20);
				movestatus = false;
			}
			teleport();
		}
	}
	void OnKeyUp(int vk) {
		movestatus = false;
		teleport();
	}
	void OnKeyDown(int vk) {
		if (GetKeyState(VK_CONTROL)<0) {
			step = 12;
		}
		else
		{
			step = 4;
		}
		movestatus = true;
		switch (vk)
		{
		case VK_LEFT:
		{
			po.x -= step;
			if (!checkForOutside(po, size))
			{
				po.x += step;
				movestatus = false;
			}
			break;
		}
		case VK_RIGHT:
		{
			po.x += step;
			if (!checkForOutside(po, size))
			{
				po.x -= step;
				movestatus = false;
			}
			break;
		}
		case VK_DOWN:
		{
			po.y += step;
			if (!checkForOutside(po, size))
			{
				po.y -= step;
				movestatus = false;
			}
			break;
		}
		case VK_UP:
		{
			po.y -= step;
			if (!checkForOutside(po, size))
			{
				po.y += step;
				movestatus = false;
			}
			break;
		}
		default:
			break;
		}
		teleport();
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
