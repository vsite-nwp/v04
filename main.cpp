#include "nwpwin.h"
class Static :public Window {
private:
	bool ismoving = false;
public:
std::string ClassName() {
	return "Static";
}
void setIsMoving(bool val) {
	ismoving = val;
}
bool getIsMoving() {
	return ismoving;
}
};


class MainWindow : public Window
{
protected:
	LONG lstyle;
	const int xoffset = -GetSystemMetrics(SM_CXFRAME) - GetSystemMetrics(SM_CXPADDEDBORDER);
	const int yoffset = -GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYFRAME) - GetSystemMetrics(SM_CXPADDEDBORDER);
	RECT r;
	RECT rveliki;
	void OnLButtonDown(POINT p) {
		if (ship == NULL) {
			ship.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "X", 101, p.x-8, p.y-8, 16, 16);
		}
		else {
			SetWindowPos((HWND)ship, 0, p.x - 8, p.y - 8,0,0,SWP_NOSIZE|SWP_NOZORDER);
		}
	}
	void OnKeyUp(int vk) {
		if (ship != NULL) {
			ship.setIsMoving(false);
			lstyle = GetWindowLong((HWND)ship, GWL_STYLE);
			lstyle |= WS_BORDER;
			SetWindowLong((HWND)ship, GWL_STYLE, lstyle);
			SetWindowPos((HWND)ship, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		
	}
	void OnKeyDown(int vk) {
		if(ship != NULL) {
			int newposx;
			int newposy;
			ship.setIsMoving(true);
			lstyle = GetWindowLong((HWND)ship, GWL_STYLE);
			lstyle &= ~(WS_BORDER);
			SetWindowLong((HWND)ship, GWL_STYLE, lstyle);
			SetWindowPos((HWND)ship, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
			GetWindowRect((HWND)ship, &r);
			GetWindowRect(*this, &rveliki);
			switch (vk) {
			case VK_LEFT:
				newposy = r.top - rveliki.top + yoffset;
					if (GetKeyState(VK_CONTROL) < 0) {
						newposx = (r.left - rveliki.left - 50) + xoffset;
						if (newposx > 0) {
							SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
						}
					}
					else {
						newposx = (r.left - rveliki.left - 10) + xoffset;
						if (newposx >0) {
							SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
						}
					}
					break;
			case VK_RIGHT:
				newposy = r.top - rveliki.top + yoffset;
				if (GetKeyState(VK_CONTROL) < 0) {
					newposx = r.left - rveliki.left + 50 + xoffset;
					if (newposx < (rveliki.right - rveliki.left) - (r.right - r.left)+xoffset) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else {
					newposx = r.left - rveliki.left + 10 + xoffset;
					if (newposx < (rveliki.right - rveliki.left-(r.right-r.left))+xoffset) {
						SetWindowPos((HWND)ship, 0,newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				break;
			case VK_UP:
				newposx = r.left - rveliki.left + xoffset;
				if (GetKeyState(VK_CONTROL) < 0) {
					newposy = r.top - 50 - rveliki.top + yoffset;
					if (newposy >0) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else {
					newposy = r.top - 10 - rveliki.top + yoffset;
					if (newposy > 0) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				break;
			case VK_DOWN:
				newposx = r.left - rveliki.left + xoffset;
				if (GetKeyState(VK_CONTROL) < 0) {
					newposy = r.top + 50 - rveliki.top + yoffset;
					if (newposy < (rveliki.bottom - rveliki.top-(r.bottom-r.top)+yoffset)) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else {
					newposy = r.top + 10 - rveliki.top + yoffset;
					if (newposy < (rveliki.bottom - rveliki.top) - (r.bottom - r.top)+yoffset) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				break;
			case VK_CONTROL:
				if (GetKeyState(VK_UP) < 0) {
					newposx = r.left - rveliki.left + xoffset;
					newposy = r.top - 50 - rveliki.top + yoffset;
					if (newposy > 0) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else if (GetKeyState(VK_DOWN) < 0) {
					newposx = r.left - rveliki.left + xoffset;
					newposy = r.top + 50 - rveliki.top + yoffset;
					if (newposy < (rveliki.bottom - rveliki.top) - (r.bottom - r.top)+yoffset) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else if (GetKeyState(VK_LEFT) < 0) {
					newposy= r.top - rveliki.top + yoffset;
					newposx = (r.left - rveliki.left - 50) + xoffset;
					if (newposx > 0) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				else if (GetKeyState(VK_RIGHT) < 0) {
					newposy = r.top - rveliki.top + yoffset;
					newposx = r.left - rveliki.left + 50 + xoffset;
					if (newposx < (rveliki.right - rveliki.left) - (r.right - r.left)+xoffset) {
						SetWindowPos((HWND)ship, 0, newposx, newposy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				break;
			}

		}
		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	Static ship;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{

	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
