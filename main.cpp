#include "nwpwin.h"
#include<Windows.h>
using namespace std;

const unsigned x = 20;
class Static : public Window{
	
public:
	string ClassName(){
		return "Static";
	}
	
};

class MainWindow : public Window
{
private:
	Static ship;
	POINT position;

protected:
	
	void OnLButtonDown(POINT p) {
		
		if (!ship) {

			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, 0, 0, x, x);
		}
			
			SetWindowPos(ship, 0, p.x, p.y, 0, 0,SS_CENTER| SWP_NOZORDER | SWP_NOSIZE);
			position = p;
		
		
		
	}
	void OnKeyUp(int vk) {
		
		if (ship) {



			::SetWindowLong(ship, GWL_STYLE, WS_VISIBLE | SS_CENTER | WS_CHILD);
			::SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
		}
	}
	void OnKeyDown(int vk) {
		
		if (ship) {


			int brzina = 3;
			if (GetKeyState(VK_CONTROL) < 0) {
				brzina = 15;
			}
			RECT rec;
			::GetClientRect(*this, &rec);

			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);

			switch (vk) {
			case VK_UP:
				position.y = position.y - brzina;
				if (position.y < rec.top) {
					position.y = rec.top;
				}
				break;
			case VK_DOWN:
				position.y = position.y + brzina;
				if (position.y > rec.bottom - x) {
					position.y = rec.bottom - x;
				}
				break;
			case VK_LEFT:
				position.x = position.x - brzina;
				if (position.x < rec.left) {
					position.x = rec.left;
				}
				break;
			case VK_RIGHT:
				position.x = position.x + brzina;
				if (position.x > rec.right - x) {
					position.x = rec.right - x;
				}
				break;
			default:
				return;
			}


			::SetWindowPos(ship, 0, position.x,position.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE |  SWP_FRAMECHANGED);


		}
	}

		void OnDestroy(){
			::PostQuitMessage(0);
		}
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
