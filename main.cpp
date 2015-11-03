#include "nwpwin.h"

#define SHIP_SIZE 20

// TODO: prepare class (Static) for a ship
class Static : public Window{
public:
	std::string ClassName(){ 
		return "STATIC"; 
	}
};


class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		if (!ship){
			ship.Create(*this, WS_CHILD | WS_VISIBLE, "X", 0, (int)p.x, (int)p.y, 20, 20);
		}
		// TODO: change current location
		SetWindowPos(ship, 0, (int)p.x, (int)p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER);
		cords = p;
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (!ship) return;
		StopRightThere();
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (ship){

			int throttle = 5;
			if (GetKeyState(VK_CONTROL) < 0)
				throttle = 20;

			GetClientRect(*this, &rec);
			
			switch (vk){
				case VK_UP:
					cords.y -= throttle;
					rec.top < cords.y ? cords.y : cords.y = rec.top;
					GoShipGo();
					break;
				case VK_DOWN:
					cords.y += throttle;
					rec.bottom - SHIP_SIZE > cords.y ? cords.y : cords.y = rec.bottom - SHIP_SIZE;
					GoShipGo();
					break;
				case VK_LEFT:
					cords.x -= throttle;
					rec.left < cords.x ? cords.x : cords.x = rec.left;
					GoShipGo();
					break;
				case VK_RIGHT:
					cords.x += throttle;
					rec.right - SHIP_SIZE > cords.x ? cords.x : cords.x = rec.right - SHIP_SIZE;
					GoShipGo();
					break;
			}

		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT cords;
	RECT rec;

	void StopRightThere(){
		SetWindowPos(ship, 0, cords.x, cords.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}

	void GoShipGo(){
		SetWindowPos(ship, 0, cords.x , cords.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
