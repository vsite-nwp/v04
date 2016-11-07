#include "nwpwin.h"

// prepare class (Static) for a ship
class Static : public Window {
public:
	std::string ClassName() override { return "STATIC"; }
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		// create ship if it doesn't exist yet
		cur_position = p;
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X" ,NULL ,cur_position.x, cur_position.y, 30, 30);
		// change current location
		SetWindowPos(ship, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		cur_position = p;
	}
	void OnKeyUp(int vk) {
		// mark ship (if exists) as "not moving"
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
			SetWindowPos(ship, NULL, cur_position.x, cur_position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
	void OnKeyDown(int vk) {
		// if ship exists, move it depending on key and mark as "moving"
		if (ship) {
			int MoveSpeed = 5;
			if (GetKeyState(VK_CONTROL) < 0)
				MoveSpeed += 30;
			RECT ship_rect;
			GetClientRect(*this, &ship_rect);
			switch (vk) {
			case VK_UP: cur_position.y = max(ship_rect.top, cur_position.y - MoveSpeed); break;
			case VK_DOWN: cur_position.y = min(ship_rect.bottom -20, cur_position.y + MoveSpeed); break;
			case VK_LEFT: cur_position.x = max(ship_rect.left, cur_position.x - MoveSpeed); break;
			case VK_RIGHT: cur_position.x = min(ship_rect.right -20, cur_position.x + MoveSpeed); break;
			default: return;
			}
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, 0, cur_position.x, cur_position.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT cur_position;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
