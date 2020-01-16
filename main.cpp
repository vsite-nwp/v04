#include "nwpwin.h"


class Static :public Window {
public:
	std::string ClassName() 
	{
		return "STATIC";
	}
};

class MainWindow : public Window
{

private:
	Static ship;
	POINT position;
	//bool onTheMove;

protected:
	void OnLButtonDown(POINT p) 
	{

		if (!ship) 
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "<>", NULL, p.x, p.y, 50, 50);
		}
		position = p;
		bool onTheMove = false;
		move(onTheMove);
	}

	void OnKeyUp(int vk) {
		
		if (!ship)
			return;
		bool onTheMove = false;
		move(onTheMove);
	}

	void OnKeyDown(int vk) {
		
		if (ship)
		{
			int speed = GetKeyState(VK_CONTROL) < 0 ? 100 : 25;
			RECT rect;
			GetClientRect(*this, &rect);

			switch (vk) {
			case (VK_LEFT):
				position.x = max(0, position.x - speed);
				break;
			case (VK_RIGHT):
				position.x = min(rect.right - 50, position.x + speed);
				break;
			case (VK_UP):
				position.y = max(0, position.y - speed);
				break;
			case(VK_DOWN):
				position.y = min(rect.bottom - 50, position.y + speed);
				break;
			default:
				return;
			}
			bool onTheMove = true;
			move(onTheMove);
		}
	}

		void OnDestroy() {
			::PostQuitMessage(0);
		}

		void move(bool onTheMove) {
			DWORD style = ::GetWindowLong(ship, GWL_STYLE);			
			style = onTheMove ? (style | WS_BORDER) : (style & ~WS_BORDER);
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, NULL, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		}
	};

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
	{
		Application app;
		MainWindow wnd;
		wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
		return app.Run();
	}
