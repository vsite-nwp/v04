#include "nwpwin.h"

#define S_SIZE 20
#define S_STEP 1
#define S_BIGSTEP 30

// TODO: prepare class (Static) for a ship
class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
	DWORD style1 = WS_CHILD | WS_VISIBLE | SS_CENTER;
	


};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
		newCoord = p;
		GetClientRect(*this, &wSize);

		coord.x = newCoord.x;
		coord.y = newCoord.y;

		if (!ship) CreateShip();

		SetWindowLong(ship, GWL_STYLE, ship.style1);
		
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (ship)
		{
			

			SetWindowLong(ship, GWL_STYLE, ship.style1 &~WS_BORDER);
			
		}
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (ship)
		{
			if (GetKeyState(VK_CONTROL) < 0) step = S_BIGSTEP;
			else step = S_STEP;
			GetClientRect(*this, &wSize);
			switch (vk)
			{
			case VK_UP:
					newCoord.y = max(0, newCoord.y - step);
					break;
			case VK_DOWN:
					newCoord.y = min(wSize.bottom-S_SIZE, newCoord.y + step);
					break;
			case VK_LEFT:
				newCoord.x = max(0, newCoord.x - step);				
				break;
			case VK_RIGHT:
				newCoord.x = min(wSize.right-S_SIZE, newCoord.x + step);								
				break;
			default:
				break;			
			}
			SetWindowLong(ship, GWL_STYLE, ship.style1 | WS_BORDER );
			coord.x = newCoord.x;
			coord.y = newCoord.y;

			SetWindowPos(ship, HWND_TOP, coord.x, coord.y, NULL, NULL, SWP_FRAMECHANGED | SWP_NOSIZE);
		
		}
	
	
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT coord, newCoord;
	RECT wSize;
	int step;

	void CreateShip()
	{
		ship.Create(*this, ship.style1, "X", NULL, coord.x, coord.y, S_SIZE, S_SIZE);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
