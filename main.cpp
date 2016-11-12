#include "nwpwin.h"


class Static :public Window {
public: 
	std::string ClassName() override { return "Static"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!s)
			s.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, 0, 0, 20, 20);
		this->p = p;
		Move();
	}
	void OnKeyUp(int vk) {
		if (!s) return;
		Move();
	}
	void OnKeyDown(int vk) {
		if (!s) return;
			int a = GetKeyState(VK_CONTROL)<0 ? 5 : 20;

			RECT window;
			::GetClientRect(*this, &window);

			switch (vk) {
			case VK_LEFT:
				p.x -= a;
				if (p.x < window.left)
					p.x = window.left;
				MarkMove();
				break;
			case VK_RIGHT:
				p.x += a;
				if (p.x > window.right-20)
					p.x = window.right-20;
				MarkMove();
				break;
			case VK_DOWN:
				p.y += a;
				if (p.y > window.bottom-20)
					p.y = window.bottom-20;
				MarkMove();
				break;
			case VK_UP:
				p.y -= a;
				if (p.y < window.top)
					p.y = window.top;
				MarkMove();
				break;
			default:
				return;
		}

	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:
	Static s;
	POINT p;
	void Move() { 
		SetWindowLong(s, GWL_STYLE, WS_CHILD | WS_VISIBLE|SS_CENTER);
		SetWindowPos(s, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER); }
	void MarkMove() {
		SetWindowLong(s, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(s, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
