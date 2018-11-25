#include "nwpwin.h"
class Static : public Window
{
public:
	std::string ClassName() override { return "STATIC"; }
};
const SIZE shipSize = { 20,20 };

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) 
	{
		if (!ship) 
			ship.Create(*this,STIL1, "X", 0, p.x, p.y, shipSize.cx, shipSize.cy);
			
		::SetWindowPos(ship, 0,p.x,p.y,0,0,STIL2);
		current_position = p;
	}
	void OnKeyUp(int vk) {

		if (ship) {
			::SetWindowLong(ship, GWL_STYLE, STIL1);
			::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0,STIL2);
			}
		}
	void OnKeyDown(int vk) {
		
		RECT rc; 
		::GetClientRect(*this, &rc);
		int step=GetAsyncKeyState(VK_CONTROL) ?  20  : 5;

			switch (vk)
			{
			case VK_UP:
				current_position.y = max(current_position.y - step, rc.top);
				break;
			case VK_DOWN:
				current_position.y = min(current_position.y + step, rc.bottom - shipSize.cy);
				break;
			case VK_LEFT:
				current_position.x = max(current_position.x - step, rc.left);
				break;
			case VK_RIGHT:
				current_position.x = min(current_position.x + step, rc.right - shipSize.cx);
				break;
			default:
				return;
			}
		
		::SetWindowLong(ship, GWL_STYLE,STIL1);
		::SetWindowPos(ship, 0, current_position.x, current_position.y, 0, 0, STIL2);
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
	POINT current_position;
	const long STIL1 = WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER;
	const long STIL2 = SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;
 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
