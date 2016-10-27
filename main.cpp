#include "nwpwin.h"

class StaticWnd : public Window {
	POINT staticPos;
	bool cntrlKeyState;
public:
	StaticWnd() : cntrlKeyState(false) {}
	std::string ClassName() override { return "STATIC"; }
	void SetStaticCntrlKey(bool cntrl) { cntrlKeyState = cntrl; }
	void SetStaticpos(const POINT point) { staticPos = point; }
	const bool GetCntrlKeyState() { return cntrlKeyState; }
	const POINT& GetStaticPos() { return staticPos; }

	void DrawChildWndFrame(bool keyUpDown) override
	{
		SetWindowLong(*this, GWL_STYLE, WS_CHILD | WS_VISIBLE | (keyUpDown ? WS_BORDER : NULL));
		SetWindowPos(*this, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
	}

	//Move child window inside parent, moveWnd specify is childwindows still inside parent
	void MoveChildWndIn(int x, int y, bool moveWnd) override
	{
		SetWindowPos(*this, NULL,
			(moveWnd ? staticPos.x += (x) : NULL),
			(moveWnd ? staticPos.y += (y) : NULL),
			0, 0,
			SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | (moveWnd ? NULL : SWP_NOMOVE));
	}
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!stWnd)
			stWnd.Create(*this, WS_CHILD | WS_VISIBLE, " x", NULL, p.x, p.y, 15, 20);
		else
			SetWindowPos(stWnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		stWnd.SetStaticpos(p);
	}
	void OnKeyUp(int vk) {
		if (vk == VK_CONTROL)
			stWnd.SetStaticCntrlKey(false);
		else if (vk == VK_LEFT || vk == VK_DOWN || vk == VK_RIGHT || vk == VK_UP)
			stWnd.DrawChildWndFrame(false);
	}
	void OnKeyDown(int vk) {
		if (stWnd)
		{
			stWnd.DrawChildWndFrame(true);
			GetClientRect(*this, &mainWndSize);

			if (vk == VK_CONTROL)
			{
				stWnd.SetStaticCntrlKey(true);
				return;
			}

			switch (vk)
			{
			case VK_LEFT:
				stWnd.GetCntrlKeyState() ? stWnd.MoveChildWndIn(-20, 0, ((stWnd.GetStaticPos().x + (-20)) > mainWndSize.left))
					: stWnd.MoveChildWndIn(-5, 0, ((stWnd.GetStaticPos().x + (-5)) > mainWndSize.left));
				break;
			case VK_UP:
				stWnd.GetCntrlKeyState() ? stWnd.MoveChildWndIn(0, -20, ((stWnd.GetStaticPos().y + (-20)) > mainWndSize.top))
					: stWnd.MoveChildWndIn(0, -5, ((stWnd.GetStaticPos().y + (-5)) > mainWndSize.top));
				break;
			case VK_DOWN:
				stWnd.GetCntrlKeyState() ? stWnd.MoveChildWndIn(0, 20, ((stWnd.GetStaticPos().y + 20) < mainWndSize.bottom))
					: stWnd.MoveChildWndIn(0, 5, ((stWnd.GetStaticPos().y + 5) < mainWndSize.bottom));
				break;
			case VK_RIGHT:
				stWnd.GetCntrlKeyState() ? stWnd.MoveChildWndIn(20, 0, ((stWnd.GetStaticPos().x + 20) < mainWndSize.right))
					: stWnd.MoveChildWndIn(5, 0, ((stWnd.GetStaticPos().x + 5) < mainWndSize.right));
				break;
			}
		}
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}

private:
	StaticWnd stWnd;
	RECT mainWndSize;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
