#include "nwpwin.h"

class Static : public Window{
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT currPos;
	LONG style;

protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE, ":)", NULL, p.x, p.y, 20, 20);
		currPos = p;
		style = GetWindowLong(st, GWL_STYLE);
		naCrtajGa(style, false);
	};

	void OnKeyUp(int vk) {
		if (st){
			naCrtajGa(style, false); 
		}
	}
	void OnKeyDown(int vk) {
		if (st)
		{
			int Speed = 5;
			if (GetKeyState(VK_LCONTROL) < 0)
				Speed = 20;

			RECT stPosition;
			GetClientRect(*this, &stPosition);

			switch (vk) {
				case (VK_LEFT) :
					currPos.x = max(0, currPos.x - Speed);
					break;
				case (VK_RIGHT) :
					currPos.x = min(stPosition.right - 20, currPos.x + Speed);
					break;
				case (VK_UP) :
					currPos.y = max(0, currPos.y - Speed);
					break;
				case(VK_DOWN) :
					currPos.y = min(stPosition.bottom - 20 , currPos.y + Speed);
					break;
				default:
					return;
				}
			naCrtajGa(style, true); 
		}
	}

	void naCrtajGa(LONG style, bool haveBorder) {
		LONG border;
		haveBorder ? border = WS_BORDER : border = NULL;
		SetWindowLong(st, GWL_STYLE, style | border);
		SetWindowPos(st,NULL, currPos.x, currPos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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