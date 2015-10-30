#include "nwpwin.h"
//Custom defines...
#define WD_WIDTH 400
#define WD_HEIGHT 400
#define SH_SIZE 20


class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
};

class MainWindow : public Window
{

protected:
	void OnLButtonDown(POINT p) {

		CheckNSetPosition(p);

		if (!ship) {
			BuildShip(position);
		}
		
		SetWindowPos(ship, HWND_TOP, position.x, position.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT position;
	RECT clientSize, perimeter;
	

	void BuildShip(POINT& p) {
		ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, SH_SIZE, SH_SIZE);
	}

	void CheckNSetPosition(POINT& p) {

		GetClientRect(*this, &clientSize);

		perimeter.bottom = clientSize.bottom - SH_SIZE;
		perimeter.right = clientSize.right - SH_SIZE;
		perimeter.top = clientSize.top;
		perimeter.left = clientSize.left;

		if (p.x > perimeter.right) {
			position.x = perimeter.right;
		}
		else{ 
			position.x = p.x; 
		}
		
		if (p.y > perimeter.bottom) {
			position.y = perimeter.bottom;
		}
		else {
			position.y = p.y;
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4",NULL,CW_USEDEFAULT, CW_USEDEFAULT,WD_WIDTH,WD_HEIGHT);
	return app.Run();
}
