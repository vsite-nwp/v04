#include "nwpwin.h"

class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, p.x, p.y, 16, 16);
		else
			SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		curPos = p;
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		RECT border;
		GetClientRect(*this, &border);
		if (ship) {
			switch (vk)
			{
			case VK_UP:
				curPos.y = max(curPos.y - 1, border.top);
				break;
			case VK_DOWN:
				curPos.y = min(curPos.y + 1, border.bottom - 16);
				break;
			case VK_LEFT:
				curPos.x = max(curPos.x - 1, border.left);
				break;
			case VK_RIGHT:
				curPos.x = min(curPos.x + 1, border.right - 16);
				break;
			default:
				return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(ship, NULL, curPos.x, curPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT curPos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
