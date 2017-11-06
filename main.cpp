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
		
		if (st)
			SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(st, 0, currpos.x, currpos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE| SWP_NOSIZE | SWP_NOZORDER);
		
			
	}
	void OnKeyDown(int vk) {
		
		RECT rect;
		GetClientRect(*this, &rect);
		int movement;
		if (GetKeyState(VK_CONTROL) & 0x8000)
			movement = 10;
		else
			movement = 1;
		switch (vk) {
		case VK_LEFT: 
			currpos.x -= movement;
			if (currpos.x < rect.left)
				currpos.x = rect.left;
			break;
		case VK_RIGHT:
			currpos.x += movement;
			if (currpos.x > rect.right-20)
				currpos.x = rect.right-20;  
			break;
		case VK_UP:
			currpos.y -= movement;
			if (currpos.y < rect.top)
				currpos.y = rect.top;
			break;
		case VK_DOWN:
			currpos.y += movement;
			if (currpos.y > rect.bottom-20)
				currpos.y = rect.bottom-20; 
			break;
		}
		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
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
