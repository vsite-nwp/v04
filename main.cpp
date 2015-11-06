#include "nwpwin.h"
#define SHIP_WIDTH 20
#define SHIP_HEIGHT 20



// TODO: prepare class (Static) for a ship
class Static : public Window {

public:
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
protected:
	POINT pos;
	Static ship;
	RECT rec;
	
	
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		if (!ship) {
			ship.Create(*this, WS_VISIBLE | WS_CHILD, "x", NULL, p.x, p.y, SHIP_WIDTH, SHIP_HEIGHT);
			pos.x = p.x;
			pos.y = p.y;
			
		}

		// TODO: change current location
		SetWindowPos(ship,NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pos.x = p.x;
		pos.y = p.y;

	}
	void OnKeyUp(int vk) {
		
		// TODO: mark ship (if exists) as "not moving"
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE);
		SetWindowPos(ship, NULL, 0, 0, 0, 0,SWP_NOSIZE | SWP_NOZORDER |SWP_NOMOVE|SWP_FRAMECHANGED);
	
		
	}
	void OnKeyDown(int vk) {

		// TODO: if ship exists, move it depending on key and mark as "moving"
		GetClientRect(*this, &rec);
		int step=20;
		if (GetKeyState(VK_CONTROL)<0) {
			step += 50;
		}
			
		
	if (vk == VK_LEFT){
		 
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, NULL, pos.x -= step, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		
	}
		else if (vk == VK_RIGHT) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, NULL, pos.x += step, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	} 
		else if(vk == VK_DOWN) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, NULL, pos.x, pos.y+=step, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}	
		else if (vk == VK_UP) {
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(ship, NULL, pos.x, pos.y-=step, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}

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

