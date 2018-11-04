#include "nwpwin.h"

class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		current_position = p;

		if (!ship)
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 1, current_position.x, current_position.y, 20, 20);
		}
		else {
			::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(ship, NULL, current_position.x, current_position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		if (ship) {

			int speed = GetKeyState(VK_CONTROL) < 0 ? 20 : 5;

			RECT window_rect;
			GetClientRect(*this, &window_rect);

			RECT ship_rect;
			GetClientRect(ship, &ship_rect);

			switch (vk) {
			case VK_UP:
				if (current_position.y - speed >= window_rect.top)
				{
					current_position.y -= speed;
				}
				break;
			case VK_DOWN: 
				if (current_position.y + ship_rect.bottom + speed <= window_rect.bottom)
				{
					current_position.y += speed;
				}
				break;
			case VK_LEFT: 
				if (current_position.x - speed >= window_rect.left)
				{
					current_position.x -= speed;
				}
				break;
			case VK_RIGHT: 
				if (current_position.x + ship_rect.right + speed <= window_rect.right)
				{
					current_position.x += speed;
				}
				break;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
