#include "nwpwin.h"


// TODO: prepare class (Static) for a ship
class Static : public Window {

public:
	std::string ClassName() override { return "STATIC"; }

};

class MainWindow : public Window
	{
	UINT key;
	Static ship;
	POINT current_pos;
	
protected:

	////////////////////////////////////////
	/*void OnSubclass(HWND hWnd)
	{

		WNDPROC oldProc = reinterpret_cast<WNDPROC>(SetWindowLong(hWnd, GWL_WNDPROC, (LONG)newProc));

	}
		static LRESULT CALLBACK newProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
		{
			if (msg == WM_CHAR)
				return 0;
			return CallWindowProc(oldProc, hw, msg, wp, lp);
		}*/
	/////////////////////////////////////////////////////

	void OnLButtonDown(POINT p) {
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x",0, p.x, p.y,20,20 );
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
	
	}
	void OnKeyUp(int vk) {
		
		// TODO: mark ship (if exists) as "not moving"
	}
	void OnKeyDown(int vk) {
		if (!ship)
			return;
		int speed;
		if (GetKeyState(VK_CONTROL) & 0x8000)
			speed = 15;
		else
			speed = 5;
		if (vk == VK_UP)
			current_pos.y -= speed;
		if (vk == VK_DOWN)
			current_pos.y += speed;
		if (vk == VK_LEFT)
			current_pos.x -= speed;
		if (vk == VK_RIGHT)
			current_pos.x += speed;
	
		SetWindowPos(ship,0,current_pos.x,current_pos.y,0,0, SWP_NOSIZE|SWP_NOZORDER);

		
		// TODO: if ship exists, move it depending on key and mark as "moving"
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
