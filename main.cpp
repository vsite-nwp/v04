#include "nwpwin.h"
#include "math.h"

// prepare class (Static) for a ship
class Static:public Window{
	std::string ClassName() override { return "STATIC"; }
	
};

class MainWindow : public Window
{
	Static st;
	POINT current_pos;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
	}
	void OnKeyUp(int vk)
	{
		Border(false);
	}
	void OnKeyDown(int vk) {
		RECT wdw;
		GetClientRect(*this, &wdw);
		int step = GetKeyState(VK_CONTROL) & 0x8000 ? 50 : 10;
		switch (vk) {
		case VK_LEFT:
			current_pos.x = max(0, current_pos.x - step);
			break;
		case VK_RIGHT:
			current_pos.x = min(wdw.right-20, current_pos.x + step);
			break;
		case VK_DOWN:
			current_pos.y = min(wdw.bottom - 20, current_pos.y + step);
			break;
		case VK_UP:
			current_pos.y = max(0, current_pos.y - step);
			break;
		}
		Border(true);
		// if ship exists, move it depending on key and mark as "moving"
	}
	void promjena()
	{
		//samo da mi proradi commit
	}
	void Border(bool on)
	{
		long style = GetWindowLong(st, GWL_STYLE);
		style = on ? style | WS_BORDER : style& ~WS_BORDER;
		SetWindowLong(st, GWL_STYLE, style);
		SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
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
