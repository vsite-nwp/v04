#include "nwpwin.h"

#define S_SIZE 20
#define S_STEP 1
#define S_BIGSTEP 30


class Static : public Window {
public:
	std::string ClassName() { return "STATIC"; }
	
	


};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		
		newCoord = p;
		GetClientRect(*this, &wSize);

		coord.x = newCoord.x;
		coord.y = newCoord.y;

		if (!ship) CreateShip();

		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		
	}
	void OnKeyUp(int vk) {
		
		if (ship)
		{			
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE); 
			SetWindowPos(ship, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
			
		}
	}
	void OnKeyDown(int vk) {
		
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
			
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			coord.x = newCoord.x;
			coord.y = newCoord.y;

			
			SetWindowPos(ship, NULL, coord.x, coord.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
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
		ship.Create(*this, WS_VISIBLE | WS_CHILD, "x", NULL, coord.x, coord.y, S_SIZE, S_SIZE);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
