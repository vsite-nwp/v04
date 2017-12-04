#include "nwpwin.h"



class Static : public Window {
	std::string ClassName() override { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT current_pos;
protected:
	void OnLButtonDown(POINT p) {
		if(!st)
			st.Create(*this,WS_CHILD | WS_VISIBLE|SS_CENTER,"x",0, p.x, p.y,20,20);
		SetWindowPos(st,0, p.x, p.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
		current_pos = p;
		
	}
	void OnKeyUp(int vk) {
		if (st)
			{
			SetWindowLong(st, GWL_STYLE, GetWindowLong(st, GWL_STYLE) & ~WS_BORDER);
			SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
			}
	}
	void OnKeyDown(int vk) {
		RECT rect;
		GetClientRect(*this, &rect);
		int step = 0;
		if (GetKeyState(VK_CONTROL) < 0)
			step = 20;
		else
			step = 5;

			if (st) {
			switch (vk) {
				case VK_UP:
					current_pos.y = max(current_pos.y - step, 0);
					break;
					case VK_DOWN:
						current_pos.y = min(current_pos.y + step, rect.bottom - 20);
						break;
						case VK_LEFT:
							current_pos.x = max(current_pos.x - step, 0);
							break;
							case VK_RIGHT:
								current_pos.x = min(current_pos.x + step, rect.right - 20);
								break;
								
			}
			SetWindowLong(st, GWL_STYLE, GetWindowLong(st, GWL_STYLE) | WS_BORDER);
			SetWindowPos(st, 0, current_pos.x, current_pos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
			
				
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
