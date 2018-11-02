#define NOMINMAX

#include "nwpwin.h"
#include <algorithm>
#include <string>

class Static : public Window {
protected: 
	std::string ClassName() override { return "STATIC"; }
};

class Edit : public Window {
protected:
	std::string ClassName() override { return "EDIT"; }
};

class MainWindow : public Window
{
private:
	Static ship;
	POINT position;
	const SIZE shipSize = {20,20};
	Edit editXCordinate, editYCordinate;

	enum { idShip = 1, idEditOne, idEditTwo };

	void refreshText() {
		SetDlgItemInt(*this, idEditOne, this->position.x, true);
		SetDlgItemInt(*this, idEditTwo, this->position.y, true);
	}

	void initComponents() {
		this->ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_CLIPSIBLINGS, "x", idShip, this->position.x, this->position.y, this->shipSize.cx, this->shipSize.cy);
		refreshText();
	}

	void setPosition() {
		::SetWindowPos(ship, 0, this->position.x, this->position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		refreshText();
	}

protected:
	int OnCreate(CREATESTRUCT* pcs){
		const DWORD editStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED | WS_CLIPSIBLINGS;

		this->editXCordinate.Create(*this, editStyle, "x:", idEditOne, 10, 10, 40, 25);
		this->editYCordinate.Create(*this, editStyle, "y:", idEditTwo, 55, 10, 40, 25);
		return 0;
	}

	void OnLButtonDown(POINT p) {
		this->position = p;	
		if (!ship) initComponents();
		else setPosition();
	}
	void OnKeyUp(int vk) {
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE) & ~WS_BORDER);
			setPosition();
		}
	}
	void OnKeyDown(int vk) {
		RECT r;
		GetClientRect(*this, &r);
		int step = GetKeyState(VK_CONTROL) < 0 ? 5 : 1;

		if (!ship) return;
		
		switch (vk) {
		case VK_UP:
			position.y = std::max(this->position.y - step, 0L);
			break;
		case VK_DOWN:
			position.y = std::min(this->position.y + step, r.bottom - this->shipSize.cy);
			break;
		case VK_LEFT:
			position.x = std::max(this->position.x - step, 0L);
			break;
		case VK_RIGHT:
			position.x = std::min(this->position.x + step, r.right - this->shipSize.cx);
			break;
		default:
			return;
		}
		::SetWindowLong(ship, GWL_STYLE, GetWindowLong(ship, GWL_STYLE) | WS_BORDER);
		setPosition();

	}

	void OnDestroy(){
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
