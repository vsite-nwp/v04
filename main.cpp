#include "nwpwin.h"

using namespace std;
class Static :public Window {
public:
	string ClassName() {
		return "STATIC";
	}
};

class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {
		if (!st)

			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", NULL, p.x, p.y, 20, 20);

		SetWindowPos(st, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
		
	}
	
	void OnKeyUp(int vk) {
		if (!st)
			return;
		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
		SetWindowPos(st, NULL, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		move(true);
	}
	
	void OnKeyDown(int vk) {
		if (st)
			
		{
			int Speed = 10;
			if (GetKeyState(VK_CONTROL) < 0)
				Speed *= 2;
			RECT rc;
			GetClientRect(*this, &rc);

			switch (vk) {
			case (VK_LEFT):
				current_pos.x = max(0, current_pos.x - Speed);
				break;
			case (VK_RIGHT):
				current_pos.x = min(rc.right - 20, current_pos.x + Speed);
				break;
			case (VK_UP):
				current_pos.y = max(0, current_pos.y - Speed);
				break;
			case(VK_DOWN):
				current_pos.y = min(rc.bottom - 20, current_pos.y + Speed);
				break;
			default:
				return;
			}
			
			SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
			SetWindowPos(st, NULL, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
			move(true);
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static st;
	POINT current_pos;

	void move(bool on) {
		DWORD stil = ::GetWindowLong(st, GWL_STYLE);
		stil= on ? (stil | WS_BORDER) : (stil&~WS_BORDER);
	}
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();

}