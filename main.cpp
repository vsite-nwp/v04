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
	SIZE shipSize = {20,20};
	Edit editXCordinate, editYCordinate;

	DWORD editStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED | WS_CLIPSIBLINGS;

	void refreshText() {
		SetDlgItemInt(*this, 001, this->position.x, true);
		SetDlgItemInt(*this, 002, this->position.y, true);
	}

	void initComponents() {
		this->ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", NULL, this->position.x, this->position.y, this->shipSize.cx, this->shipSize.cy);
		refreshText();
	}

	void setPosition() {
		::SetWindowPos(ship, HWND_TOP, this->position.x, this->position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);
		refreshText();
	}

protected:
	int MainWindow::OnCreate(CREATESTRUCT* pcs){
		this->editXCordinate.Create(*this, editStyle, "x:", 001, 10, 10, 40, 25);
		this->editYCordinate.Create(*this, editStyle, "y:", 002, 55, 10, 40, 25);
		return 0;
	}

	void OnLButtonDown(POINT p) {
		this->position = p;	
		ship == nullptr ? initComponents() : setPosition();
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
			position.y = max(this->position.y - step, 0);
			break;
		case VK_DOWN:
			position.y = min(this->position.y + step, r.bottom - this->shipSize.cy);
			break;
		case VK_LEFT:
			position.x = max(this->position.x - step, 0);
			break;
		case VK_RIGHT:
			position.x = min(this->position.x + step, r.right - this->shipSize.cx);
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
