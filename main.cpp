#include "nwpwin.h"

#define SHIP_WIDTH 20
#define SHIP_HEIGTH 20
#define SHIP_SPEED 5

// TODO: prepare class (Static) for a ship

class Static : public Window {
public: std::string ClassName() override {
	return "static";
}
};

class MainWindow : public Window
{
	RECT background;
	Static ship;
	int width;
	int height;
	int speed;
	bool isMoving;
	POINT position;

	void shipMoving() {
		DWORD info = GetWindowLong(ship, GWL_STYLE);

		if (this->isMoving == true)
			SetWindowLong(ship, GWL_STYLE, info | WS_BORDER);
		else
			SetWindowLong(ship, GWL_STYLE, info& ~WS_BORDER);

		SetWindowPos(ship, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}

	void goLeft() {
		if (position.x > background.left) {
			position.x -= getShipSpeed();
			this->isMoving = true;
		}
	}

	void goRight() {
		if (position.x < background.right - getShipWidth()) {
			position.x += getShipSpeed();
			this->isMoving = true;
		}
	}

	void goDown() {
		if (position.y < background.bottom - getShipHeight()) {
			position.y += getShipSpeed();
			this->isMoving = true;
		}
	}

	void goUp() {
		if (position.y > background.top) {
			position.y -= getShipSpeed();
			this->isMoving = true;
		}
	}

public:
	void setShipWidth(int width) {
		this->width = width;
	}
	void setShipHeight(int height) {
		this->height = height;
	}
	void setShipSpeed(int speed) {
		this->speed = speed;
	}
	int getShipWidth() { return this->width; }
	int getShipHeight() { return this->height; }
	int getShipSpeed() { return this->speed; }

protected:
	void OnLButtonDown(POINT p) {
		// TODO: create ship if it doesn't exist yet
		if (!ship)
			ship.Create(*this, WS_CHILD | WS_VISIBLE, "X", 0, p.x, p.y, this->getShipWidth(), this->getShipHeight());
		// TODO: change current location
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		position = p;
	}
	void OnKeyUp(int vk) {
		// TODO: mark ship (if exists) as "not moving"
		if (ship) {
			this->isMoving = false;
			if (getShipSpeed() > SHIP_SPEED)
				setShipSpeed(SHIP_SPEED);
			shipMoving();
		}
	}
	void OnKeyDown(int vk) {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		if (!ship)
			return;
		GetClientRect(*this, &background);
		// poveæanje brzine
		if (GetKeyState(VK_LCONTROL) < 0)
			setShipSpeed(SHIP_SPEED * 2);
		else
			setShipSpeed(SHIP_SPEED);

		switch (vk) {
		case VK_LEFT:
			goLeft();
			break;
		case VK_RIGHT:
			goRight();
			break;
		case VK_DOWN:
			goDown();
			break;
		case VK_UP:
			goUp();
			break;
		}

		shipMoving();
	}


	void OnDestroy() {
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	// inicijalizacija
	wnd.setShipHeight(SHIP_HEIGTH);
	wnd.setShipWidth(SHIP_WIDTH);

	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
