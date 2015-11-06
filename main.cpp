#include "nwpwin.h"
//Custom defines...
#define WD_WIDTH 400
#define WD_HEIGHT 400
#define SH_SIZE 20
#define SH_SMALLSTEP 1
#define SH_BIGSTEP 10



class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
	DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		target = p;
		GetClientRect(*this, &clientSize);

		if ((target.x + SH_SIZE) > clientSize.right) target.x = clientSize.right - SH_SIZE;
		else if (target.x < clientSize.left) target.x = clientSize.left;

		if ((target.y+SH_SIZE) > clientSize.bottom) target.y = clientSize.bottom - SH_SIZE;
		else if (target.y < clientSize.top) target.y = clientSize.top;
		
		position.y = target.y;
		position.x = target.x;

		if (!ship) BuildShip();
		
		SetWindowLong(ship, GWL_STYLE, ship.style);
		SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void OnKeyUp(int vk) {
		if (ship) 
		{
			switch (vk) 
			{
			case VK_UP:
			case VK_DOWN:
			case VK_LEFT:
			case VK_RIGHT:
				break;
			case VK_CONTROL:
				step = SH_SMALLSTEP;
				break;
			default:
				break;
			}
			SetWindowLong(ship, GWL_STYLE, ship.style);
			SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}

	void OnKeyDown(int vk) {
		if (ship) {
			if (GetKeyState(VK_CONTROL) < 0) step = SH_BIGSTEP;
			GetClientRect(*this, &clientSize);
				switch (vk)
				{
				case VK_UP:
					target.y = position.y - step;
					if (target.y < clientSize.top) target.y = clientSize.top;
					break;
				case VK_DOWN:
					target.y = position.y + step;
					if ((target.y + SH_SIZE) > clientSize.bottom) target.y = clientSize.bottom - SH_SIZE;
					break;
				case VK_LEFT:
					target.x = position.x - step;
					if (target.x < clientSize.left) target.x = clientSize.left;
					break;
				case VK_RIGHT:
					target.x = position.x + step;
					if ((target.x + SH_SIZE) > clientSize.right) target.x = clientSize.right - SH_SIZE;
					break;
				default:
					break;
				}
				SetWindowLong(ship, GWL_STYLE, ship.style | WS_BORDER);
				position.x = target.x;
				position.y = target.y;
				SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
	}

	void OnDestroy(){
		::PostQuitMessage(0);
	}

private:
	Static ship;
	POINT position, target;
	RECT clientSize;
	int step = SH_SMALLSTEP;
	
	void BuildShip() {
		ship.Create(*this, ship.style, "X", NULL, position.x, position.y, SH_SIZE, SH_SIZE);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4",NULL,CW_USEDEFAULT, CW_USEDEFAULT,WD_WIDTH,WD_HEIGHT);
	return app.Run();
}
