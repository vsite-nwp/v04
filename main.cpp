#include "nwpwin.h"
#define SHIP_ID 1

// TODO: prepare class (Static) for a ship

class Static : public Window
{
	std::string ClassName(){ return "static"; }
};

class MainWindow : public Window
{
public:
	Static s;
	POINT cp;
	RECT rect;
protected:
	void OnLButtonDown(POINT p) {
		if (!s)
		{		
			s.Create(*this, WS_CHILD | WS_VISIBLE, "X", SHIP_ID, p.x, p.y, 15, 20);			
			cp = p;
		}
		else
		{
			SetWindowPos(s, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			cp = p;
		}
	}
	void OnKeyUp(int vk) {
		if (s)
		{
			SetWindowLong(s, GWL_STYLE, WS_VISIBLE | WS_CHILD);
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		}

		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk)
	{		

		if (s &&((vk == VK_LEFT && cp.x > rect.left) || (vk == VK_RIGHT&& cp.x < rect.right) || (vk == VK_UP && cp.y > rect.top) || (vk == VK_DOWN && cp.y < rect.bottom)))
		{
			GetClientRect(*this, &rect);
			rect.bottom -= 20;
			rect.right -= 15;

			int brzina = GetAsyncKeyState(VK_CONTROL) ? 10 : 1;

			switch (vk)
			{
			case VK_LEFT:
				cp.x = cp.x - 1 * brzina;
				break;
			case VK_RIGHT:
				cp.x = cp.x + 1 * brzina;
				break;
			case VK_UP:
				cp.y = cp.y - 1 * brzina;
				break;
			case VK_DOWN:
				cp.y = cp.y + 1 * brzina;
				break;
			}
			SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		// TODO: if ship exists, move it depending on key and mark as "moving"

		SetWindowLong(s, GWL_STYLE, WS_VISIBLE | WS_BORDER | WS_CHILD);
		SetWindowPos(s, NULL, cp.x, cp.y, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
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
