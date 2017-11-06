#include "nwpwin.h"

class Static :public Window {
	std::string ClassName() override 
	{
		return "STATIC";
	}
	
};
class MainWindow : public Window
{
	Static st;
	POINT cur;
protected:
	void OnLButtonDown(POINT p) {
		if (!st) 
		{
			st.Create(*this,WS_CHILD|WS_VISIBLE|SS_CENTER,"x", 0,p.x, p.y,20,20);
		}
		SetWindowPos(st, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		cur = p;
	}
	void OnKeyUp(int vk) {
		if(st)
		{
			SetWindowLong(st, GWL_STYLE, WS_CHILD|WS_VISIBLE|SS_CENTER);
			SetWindowPos(st, 0, cur.x, cur.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
		}
		
	}
	void OnKeyDown(int vk) {

		RECT r;
		GetClientRect(*this, &r);
		bool ctrl = GetKeyState(VK_CONTROL)<0;
		if (st) {
			switch (vk) {
			case VK_UP:
				if (ctrl)
					cur.y -= 20;
				else
					cur.y -= 5;
				if (cur.y < r.top)
					cur.y = r.top;
				break;
			case VK_DOWN:
				if (ctrl)
					cur.y += 20;
				else
					cur.y += 5;
				if (cur.y > r.bottom - 20)
					cur.y = r.bottom - 20;
				break;
			case VK_LEFT:
				if (ctrl)
					cur.x -= 20;
				else
					cur.x -= 5;
				if (cur.x <r.left)
					cur.x = r.left;
				break;
			case VK_RIGHT:
				if (ctrl)
					cur.x += 20;
				else
					cur.x += 5;
				if (cur.x > r.right-20)
					cur.x = r.right-20;
				break;
			}
			SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(st, 0, cur.x, cur.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
			
		}
		
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
