#include "nwpwin.h"

// TODO: prepare class (Static) for a ship
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
	bool onTheMove;

protected:
	void OnLButtonDown(POINT p) 
	{
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
		if (!ship) 
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "<>", NULL, p.x, p.y, 50, 50);
		}
		position = p;
		onTheMove = false;
		move();
	}

	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (!ship)
			return;
		onTheMove = false;
		move();
	}

	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
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
			onTheMove = true;
			move();
		}
	}

		void OnDestroy() {
			::PostQuitMessage(0);
		}

		void move() {
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
