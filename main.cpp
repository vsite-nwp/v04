#include "nwpwin.h"

class Static : public Window{
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT currPos;
	int border;
	int sizeX = 20;
	int sizeY = 20;

protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE, ":)", NULL, p.x, p.y, sizeX, sizeY);
		currPos = p;
		naCrtajGa(NULL);
	};

	void OnKeyUp(int vk) {
		if (st){
			naCrtajGa(NULL);
		}
	}
	void OnKeyDown(int vk) {
		if (st)
		{
			int Speed = 5;
			if (GetKeyState(VK_LCONTROL) == -128)
				Speed = 20;

			RECT stPosition;
			GetClientRect(*this, &stPosition);

			switch (vk) {
				case (VK_LEFT) :
					currPos.x = max(0, currPos.x - Speed);
					break;
				case (VK_RIGHT) :
					currPos.x = min(stPosition.right - sizeX, currPos.x + Speed);
					break;
				case (VK_UP) :
					currPos.y = max(0, currPos.y - Speed);
					break;
				case(VK_DOWN) :
					currPos.y = min(stPosition.bottom - sizeY , currPos.y + Speed);
					break;
				default:
					return;
				}
				naCrtajGa(WS_BORDER);
		}
	}

	void naCrtajGa(int border) {
		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | border);
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