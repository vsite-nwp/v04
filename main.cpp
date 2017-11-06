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
		RECT rect;
		GetClientRect(*this, &rect);
		switch (vk) {
		case VK_LEFT: 
			currpos.x -= 1;
			if (currpos.x < rect.left)
				currpos.x = rect.left;
			break;
		case VK_RIGHT:
			currpos.x += 1;
			if (currpos.x > rect.right-20)
				currpos.x = rect.right-20;  //the width of the ship is 20
			break;
		case VK_UP:
			currpos.y -= 1;
			if (currpos.y < rect.top)
				currpos.y = rect.top;
			break;
		case VK_DOWN:
			currpos.y += 1;
			if (currpos.y > rect.bottom-20)
				currpos.y = rect.bottom-20; //the height of the ship is 20
			break;
		}
		SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		
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
