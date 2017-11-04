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
			st.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", NULL, p.x, p.y, 20, 20);

		SetWindowPos(st, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		current_pos = p;
	}
	
	void OnKeyUp(int vk) {
		if (!st)
			return;
		else
			SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE);
		SetWindowPos(st, NULL, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static st;
	POINT current_pos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
