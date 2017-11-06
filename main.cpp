#include "nwpwin.h"

// TODO: prepare class (Static) for a ship

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
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (st)
				SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOMOVE| SWP_NOSIZE | SWP_NOZORDER);
		
			//SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		switch (vk) {
		case VK_LEFT: 
			currpos.x -= 1;
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			break;
		case VK_RIGHT:
			currpos.x += 1;
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			break;
		case VK_UP:
			currpos.y -= 1;
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			break;
		case VK_DOWN:
			currpos.y += 1;
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			break;
		}
		/*vk = WM_KEYDOWN;
		if (GetAsyncKeyState(VK_LEFT)) {
			while (!vk) {
				SetWindowPos(st, 0, 2 + currpos.x, 2 + currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
		}*/
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
	RECT rect;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	GetClientRect(HWND(wnd), &rect);
	ClipCursor(&rect);
	return app.Run();
}
