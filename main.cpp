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
		SetWindowLongPtr(st, GWL_STYLE, WS_VISIBLE | WS_CHILD);
		SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);	
	}
	void OnKeyDown(int vk) {
		if (!st)
			return;
		RECT r, s;
		LPRECT cr = &r;
		LPRECT sr = &s;
		GetClientRect(*this, cr);
		GetClientRect(st, sr);
		int step = 1;
		int bend = cr->bottom - sr->bottom - 5;
		int rend = cr->right - sr->right - 5;

		if (GetKeyState(VK_CONTROL) < 0)
			step *= 8;
		switch (vk)
		{
		case VK_UP:
			if (current_pos.y < cr->top) {
				current_pos.y = cr->top;
				break;
			}
			current_pos.y -= step;
			break;
		case VK_DOWN:
			if (current_pos.y > bend) {
				current_pos.y = bend;
				break;
			}
			current_pos.y += step;
			break;
		case VK_LEFT:
			if (current_pos.x < cr->left ) {
				current_pos.x = cr->left;
				break;
			}
			current_pos.x -= step;
			break;
		case VK_RIGHT:
			if (current_pos.x > rend){
				current_pos.x = rend;
				break;
		}
			current_pos.x += step;
			break;
		}
		SetWindowLongPtr(st, GWL_STYLE, WS_BORDER | WS_VISIBLE | WS_CHILD);
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
