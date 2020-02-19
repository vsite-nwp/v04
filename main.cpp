#include "nwpwin.h"
#define WINDOWSIZE 16
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
	const int xoffset = GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
	const int yoffset = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
	void OnLButtonDown(POINT p) {
		if (ship == NULL) {
			ship.Create(*this, WS_VISIBLE |WS_CHILD| WS_BORDER, "X", 101, p.x-WINDOWSIZE/2, p.y- WINDOWSIZE / 2, WINDOWSIZE, WINDOWSIZE);
		}
		else {
			SetWindowPos((HWND)ship, 0, p.x - WINDOWSIZE / 2, p.y - WINDOWSIZE / 2,0,0,SWP_NOSIZE|SWP_NOZORDER);
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
		const int STEP = 10;
		const int BIGSTEP = 50;
		RECT r;
		RECT rveliki;
		if(ship != NULL) {
			ship.setIsMoving(true);
			lstyle = GetWindowLong((HWND)ship, GWL_STYLE);
			lstyle &= ~(WS_BORDER);
			SetWindowLong((HWND)ship, GWL_STYLE, lstyle);
			GetWindowRect(*this, &rveliki);
			int visina = rveliki.bottom-rveliki.top-yoffset;
			int sirina = rveliki.right-rveliki.left-2*xoffset;
			SetWindowPos((HWND)ship, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
			GetWindowRect((HWND)ship, &r);
			r.top -= rveliki.top+yoffset;
			r.bottom -= rveliki.bottom+yoffset;
			r.left -= rveliki.left+xoffset;
			r.right -= rveliki.right+xoffset;
			switch (vk) {
			case VK_LEFT:
					if (GetKeyState(VK_CONTROL) < 0) {
						BigStep(ship,vk, BIGSTEP, r, visina, sirina);
					}
					else {
						if ((r.left-STEP) < 0) {
							r.left = 0;
						}
						else {
							r.left -= STEP;
						}
						MoveShip(ship, r);
					}
					break;
			case VK_RIGHT:
				if (GetKeyState(VK_CONTROL) < 0) {
					BigStep(ship, vk, BIGSTEP, r, visina, sirina);
				}
				else {
					if ((r.left + STEP) > sirina-WINDOWSIZE) {
						r.left = sirina-WINDOWSIZE;
					}
					else {
						r.left += STEP;
					}
					MoveShip(ship, r);
				}
				break;
			case VK_UP:
				if (GetKeyState(VK_CONTROL) < 0) {
					BigStep(ship, vk, BIGSTEP, r, visina, sirina);
				}
				else {
					if ((r.top - STEP) <0) {
						r.top = 0;
					}
					else {
						r.top -= STEP;
					}
					MoveShip(ship, r);
				}
				break;
			case VK_DOWN:
				if (GetKeyState(VK_CONTROL) < 0) {
					BigStep(ship, vk, BIGSTEP, r, visina, sirina);
				}
				else {
					if ((r.top + STEP) > (visina - WINDOWSIZE)) {
						r.top = visina - WINDOWSIZE;
					}
					else {
						r.top += STEP;
					}
					MoveShip(ship, r);
				}
				break;
			case VK_CONTROL:
				if (GetKeyState(VK_UP) < 0) {
					BigStep(ship, VK_UP, BIGSTEP, r, visina, sirina);
				}
				else if (GetKeyState(VK_DOWN) < 0) {
					BigStep(ship, VK_DOWN, BIGSTEP, r, visina, sirina);
				}
				else if (GetKeyState(VK_LEFT) < 0) {
					BigStep(ship, VK_LEFT, BIGSTEP, r, visina, sirina);
				}
				else if (GetKeyState(VK_RIGHT) < 0) {
					BigStep(ship, VK_RIGHT, BIGSTEP, r, visina, sirina);
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
	void MoveShip(Static& ship,RECT r) {
		SetWindowPos((HWND)ship,0, r.left, r.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void BigStep(Static& ship,int key,int step,RECT r, int visina,int sirina) {
		switch (key) {
		case VK_LEFT:
			if ((r.left - step) < 0) {
				r.left = 0;
			}
			else {
				r.left -= step;
			}
			MoveShip(ship, r);
			break;
		case VK_RIGHT:
			if ((r.left + step) >( sirina - WINDOWSIZE)) {
				r.left = sirina - WINDOWSIZE;
			}
			else {
				r.left += step;
			}
			MoveShip(ship, r);
			break;
		case VK_UP:
			if ((r.top - step) < 0) {
				r.top = 0;
			}
			else {
				r.top -= step;
			}
			MoveShip(ship, r);
			break;
		case VK_DOWN:
			if ((r.top + step) > visina - WINDOWSIZE) {
				r.top = visina - WINDOWSIZE;
			}
			else {
				r.top += step;
			}
			MoveShip(ship, r);
			break;
		}
	}
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{

	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
