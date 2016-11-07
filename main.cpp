#include "nwpwin.h"

class StaticWnd : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
private:
	StaticWnd stWnd;
	int staticBehavior;
	POINT staticPos;
	RECT mainWndSize;
public:
	MainWindow(): staticBehavior(0){}

	void SetStaticPos(int vk) 
	{
		switch (vk)
		{
		case VK_LEFT:
			if ((staticPos.x - staticBehavior) > mainWndSize.left)
				staticPos.x -= staticBehavior;
			break;
		case VK_RIGHT:
			if ((staticPos.x + staticBehavior) < mainWndSize.right)
				staticPos.x += staticBehavior;
			break;
		case VK_DOWN:
			if ((staticPos.y + staticBehavior) < mainWndSize.bottom)
				staticPos.y += staticBehavior;
			break;
		case VK_UP:
			if ((staticPos.y - staticBehavior) > mainWndSize.top)
				staticPos.y -= staticBehavior;
			break;
		}
	}

	void DrawStaticdWndFrame(int vk, bool keyUpDown)
	{
		if (vk == VK_LEFT || vk == VK_DOWN || vk == VK_RIGHT || vk == VK_UP)
		{
			SetWindowLong(stWnd, GWL_STYLE, WS_CHILD | WS_VISIBLE | (keyUpDown ? WS_BORDER : 0));
			SetWindowPos(stWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
		}
	}

	void MoveStaticWndIn()
	{
		SetWindowPos(stWnd, NULL, staticPos.x, staticPos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

protected:
	void OnLButtonDown(POINT p) {
		if (!stWnd)
			stWnd.Create(*this, WS_CHILD | WS_VISIBLE, " x", NULL, p.x, p.y, 15, 20);
		else
			SetWindowPos(stWnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		staticPos = p;
	}

	void OnKeyUp(int vk) {
		if (GetKeyState(VK_CONTROL) >= 0)
			staticBehavior = 5;

		DrawStaticdWndFrame(vk, false);
	}

	void OnKeyDown(int vk) {
		if (stWnd)
		{
			GetClientRect(*this, &mainWndSize);

			GetKeyState(VK_CONTROL) < 0 ? staticBehavior = 15 : staticBehavior = 5;

			SetStaticPos(vk);
			
			DrawStaticdWndFrame(vk, true);

			MoveStaticWndIn();
		}
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
