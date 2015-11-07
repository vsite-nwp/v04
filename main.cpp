#include "nwpwin.h"
#define SHIP_WIDTH 20	 
#define SHIP_HEIGHT 20	//veli?ina broda u pixelima
#define NORMAL_STEP 25  //korak kretnje broda bez CTRL
#define BIG_STEP 50    //korak kretnje broda sa CTRL

class Static : public Window {

public:
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
protected:
	POINT pos;
	Static ship;
	
	
	void OnLButtonDown(POINT p) {
		
		if (!ship) {
			ship.Create(*this, WS_VISIBLE | WS_CHILD, "x", NULL, p.x, p.y, SHIP_WIDTH, SHIP_HEIGHT);
			pos.x = p.x;
			pos.y = p.y;
		} //kreiraj brod i zapamti vrijednosti koordinata
		
		SetWindowPos(ship,NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		pos.x = p.x;
		pos.y = p.y; //promijeni koordinate broda i zapamti nove vrijednosti
} 
	void OnKeyUp(int vk) {
		
		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE); //promijeni izgled ukoliko brod stoji
		SetWindowPos(ship, NULL, 0, 0, 0, 0,SWP_NOSIZE |SWP_NOMOVE|SWP_FRAMECHANGED);
	
		
	}
	void OnKeyDown(int vk) {
		
		RECT rect;
		GetClientRect(*this, &rect);	//saznaj koordinate glavnog prozora
		int step=NORMAL_STEP;
		if (GetKeyState(VK_CONTROL)<0) {
			step += BIG_STEP;
		}
			
	if (vk == VK_LEFT){
		if (pos.x>0){
			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);//ako brod ne stoji, promijeni rub broda
			SetWindowPos(ship, NULL, pos.x -= step, pos.y, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED);
			}
	}
		else if (vk == VK_RIGHT) {
			if (pos.x < (rect.right-NORMAL_STEP)) {
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowPos(ship, NULL, pos.x += step, pos.y, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
			}
	} 
		else if(vk == VK_DOWN) {
			if (pos.y <(rect.bottom - NORMAL_STEP)) {
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowPos(ship, NULL, pos.x, pos.y += step, 0, 0, SWP_NOSIZE |SWP_NOZORDER| SWP_FRAMECHANGED);
			}
	}	
		else if (vk == VK_UP) {
			if (pos.y>0) {
				SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowPos(ship, NULL, pos.x, pos.y -= step, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
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

