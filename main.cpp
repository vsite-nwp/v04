#include "nwpwin.h"

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
		if (!ship)
			ship.Create(*this, style, "X", 0, p.x, p.y, 20, 20);
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pos = p;
	}
	void OnKeyUp(int vk) {
		::SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		const int speed = GetAsyncKeyState(VK_CONTROL) ? 9 : 3;

		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk)
		{
		case VK_UP:
			pos.y = max(pos.y - speed, rect.top);
			break;
		case VK_DOWN:
			pos.y = min(pos.y + speed, rect.bottom - 20);
			break;
		case VK_LEFT:
			pos.x = max(pos.x - speed, rect.left);
			break;
		case VK_RIGHT:
			pos.x = min(pos.x + speed, rect.right - 20);
			break;
		default:
			return;
		}

		::SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
		SetWindowPos(ship, 0, pos.x, pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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