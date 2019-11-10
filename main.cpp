#include "nwpwin.h"

class Static :public Window {
public:
	std::string ClassName() {
		return "STATIC";
	}
};
class MainWindow : public Window
{
private:
	Static ship;
	POINT currentPos;
	bool isMoving;

protected:
	void OnLButtonDown(POINT p) {
		if (!ship) {
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, 20, 20);
		}
		currentPos = p;
		isMoving = false;
		move();
	}

	void OnKeyUp(int vk) {
		if (!ship)
			return;
		isMoving = false;
		move();
	}

	void OnKeyDown(int vk) {

		if (ship)
		{
			int speed = GetKeyState(VK_CONTROL) < 0 ? 30 : 15;
			RECT rect;
			GetClientRect(*this, &rect);

			switch (vk) {
				case (VK_LEFT):
					currentPos.x = max(0, currentPos.x - speed);
					break;
				case (VK_RIGHT):
					currentPos.x = min(rect.right - 20, currentPos.x + speed);
					break;
				case (VK_UP):
					currentPos.y = max(0, currentPos.y - speed);
					break;
				case(VK_DOWN):
					currentPos.y = min(rect.bottom - 20, currentPos.y + speed);
					break;
				default:
					return;
			}
			isMoving = true;
			move();
		}
	}

	void OnDestroy(){
		::PostQuitMessage(0);
	}

	void move() {
		DWORD style = ::GetWindowLong(ship, GWL_STYLE);
		style = isMoving ? (style | WS_BORDER) : (style & ~WS_BORDER);
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, NULL, currentPos.x, currentPos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "move the ship!!");
	return app.Run();
}
