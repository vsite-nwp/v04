#include "nwpwin.h"

class Static : public Window{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
	Static st;
	POINT current_pos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
	}
	void OnKeyUp(int vk) {
		if (!st)
			return;
		SetWindowLongPtr(st, GWL_STYLE, GetWindowLongPtr(st, GWL_STYLE) & ~WS_BORDER);
		SetWindowPos(st, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);	
	}
	void OnKeyDown(int vk) {
		if (!st)
			return;
		RECT cr;
		GetClientRect(*this, &cr);
		int step = GetKeyState(VK_CONTROL) < 0 ? 12 : 3;
		switch (vk)
		{
		case VK_UP: current_pos.y = max(0, current_pos.y - step); break;
		case VK_DOWN: current_pos.y = min( cr.bottom - 20, current_pos.y + step); break;
		case VK_LEFT: current_pos.x = max(0, current_pos.x - step); break;
		case VK_RIGHT: current_pos.x = min(cr.right - 20, current_pos.x + step); break;
		default: return;
		}
		SetWindowLongPtr(st, GWL_STYLE, GetWindowLongPtr(st, GWL_STYLE) | WS_BORDER );
		SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
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
