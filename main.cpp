#include "nwpwin.h"
#define SHIP_ID 1

// TODO: prepare class (Static) for a ship

class Static : public Window
{
	std::string ClassName(){ return "static"; }
};

class MainWindow : public Window
{
public:
	Static s;
	POINT cp;
	RECT rect;
	bool ctrlPritisnut = false;
protected:
	void OnLButtonDown(POINT p) {
		if (!s)
		{
			GetClientRect(*this, &rect);
			s.Create(*this, WS_CHILD | WS_VISIBLE, "X", SHIP_ID, p.x, p.y, 15, 20);
			rect.bottom -= 20;
			rect.right -= 15;
			cp = p;
		}
	}
	void OnKeyUp(int vk) {
		if (vk == 17) ctrlPritisnut = false;

		SetWindowLong(s, GWL_STYLE, WS_VISIBLE | WS_CHILD);
		SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk)
	{
		if (vk == 17) ctrlPritisnut = true;
		if (vk == 37 && cp.x > rect.left)
		{
			cp.x = cp.x - 1 * (ctrlPritisnut ? 10 : 1);
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		else if (vk == 39 && cp.x < rect.right)
		{
			cp.x = cp.x + 1 * (ctrlPritisnut ? 10 : 1);
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		else if (vk == 38 && cp.y > rect.top)
		{
			cp.y = cp.y - 1 * (ctrlPritisnut ? 10 : 1);
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		else if (vk == 40 && cp.y < rect.bottom)
		{
			cp.y = cp.y + 1 * (ctrlPritisnut ? 10 : 1);
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		// TODO: if ship exists, move it depending on key and mark as "moving"

		SetWindowLong(s, GWL_STYLE, WS_VISIBLE | WS_BORDER | WS_CHILD);
		SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
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
