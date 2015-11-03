#include "nwpwin.h"

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
			ship.Create(*this, WS_CHILD | WS_VISIBLE, "X", 0, (int)p.x, (int)p.y, 15, 15);
			cords = p;
		}
		// TODO: change current location
	
		SetWindowPos(ship, 0, (int)p.x, (int)p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER);
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
	/*	if (ship){
			SetWindowLong(ship, GWL_STYLE, ~WS_BORDER);
		}*/
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (ship){

			GetClientRect(*this, &rec);
			
			switch (vk){
				case VK_UP:
					cords.y -= 5;
					SetWindowPos(ship, 0, cords.x, rec.top < cords.y ? cords.y : rec.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER );
						break;
				case VK_DOWN:
					cords.y += 5;
					SetWindowPos(ship, 0, cords.x, rec.bottom > cords.y ? cords.y : rec.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER );
					break;
				case VK_LEFT:
					cords.x -= 5;
					SetWindowPos(ship, 0, rec.left < cords.x ? cords.x : rec.left, cords.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER );
					break;
				case VK_RIGHT:
					cords.x += 5;
					SetWindowPos(ship, 0, rec.right > cords.x ? cords.x : rec.right, cords.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SS_CENTER );
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
	POINT cords;
	RECT rec;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
