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
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		target = p;
		CheckNSetPosition(target);

		if (!ship) BuildShip();
		
		TeleportShip();
	}

	void OnKeyUp(int vk) {
		if(ship) StopShip();
	}

	void OnKeyDown(int vk) {
		if (ship) {
			int step = SH_SMALLSTEP;
			if (GetKeyState(VK_CONTROL) < 0) step = SH_BIGSTEP;
			SetWindowLong(ship, GWL_STYLE, moveStyle);
			
			switch (vk)
			{
			case VK_UP: 
				target.y = position.y - step;
				CheckNSetPosition(target);
				MoveShip();
				break;
			case VK_DOWN:
				target.y = position.y + step;
				CheckNSetPosition(target);
				MoveShip();
				break;
			case VK_LEFT:
				target.x=position.x - step;
				CheckNSetPosition(target);
				MoveShip();
				break;
			case VK_RIGHT:
				target.x =position.x + step;
				CheckNSetPosition(target);
				MoveShip();
				break;
			default:
				break;
			}
		}
	}

	void OnDestroy(){
		::PostQuitMessage(0);
	}

private:
	Static ship;
	POINT position, target;
	RECT clientSize, perimeter;
	DWORD style= WS_CHILD | WS_VISIBLE | SS_CENTER;
	DWORD moveStyle = style | WS_BORDER;
	
	void BuildShip() {
		ship.Create(*this, style, "X", NULL, position.x, position.y, SH_SIZE, SH_SIZE);
	}

	void TeleportShip() {
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void StopShip() {
		SetWindowLong(ship, GWL_STYLE, style);
		SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}

	void MoveShip() {
		SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL,SWP_FRAMECHANGED| SWP_NOSIZE | SWP_NOZORDER);
	}

	void CheckNSetPosition(POINT& p) {

		GetClientRect(*this, &clientSize);

		perimeter.bottom = clientSize.bottom - SH_SIZE;
		perimeter.right = clientSize.right - SH_SIZE;
		perimeter.top = clientSize.top;
		perimeter.left = clientSize.left;

		if (p.x > perimeter.right) p.x = perimeter.right;

		if (p.y > perimeter.bottom) p.y = perimeter.bottom;
		
		if (p.x < perimeter.left) p.x = perimeter.left;

		if (p.y < perimeter.top) p.y = perimeter.top;

		position.y = p.y;
		position.x = p.x;
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4",NULL,CW_USEDEFAULT, CW_USEDEFAULT,WD_WIDTH,WD_HEIGHT);
	return app.Run();
}
