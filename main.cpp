#include "nwpwin.h"

class Static : public Window {
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
	Static st;
	POINT currpos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD|WS_VISIBLE|SS_CENTER, "X", 0, p.x, p.y, 20, 20);
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
		currpos = p;
	}
	void OnKeyUp(int vk) {
		
		if (st) {
			SetWindowLong(st, GWL_STYLE, GetWindowLong(st, GWL_STYLE) & ~WS_BORDER);
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		
		RECT rect;
		GetClientRect(*this, &rect);
		int movement;
		movement = (GetKeyState(VK_CONTROL) < 0) ? 10 : 1;
		switch (vk) {
		case VK_LEFT: currpos.x = max(currpos.x - movement , rect.left); break;
		case VK_RIGHT:currpos.x = min(currpos.x + movement , rect.right - 20); break;
		case VK_UP: currpos.y = max(currpos.y - movement , rect.top); break;
		case VK_DOWN: currpos.y = min(currpos.y + movement , rect.bottom - 20); break;
		}
		SetWindowLong(st, GWL_STYLE, GetWindowLong(st, GWL_STYLE) | WS_BORDER);
		SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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
