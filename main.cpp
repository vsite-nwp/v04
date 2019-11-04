#include "nwpwin.h"

class Static : public Window {

public: std::string ClassName() override { 

	return "static"; }
};

class MainWindow : public Window
{
	RECT mSea;
	Static mShip;
	POINT mCurretnPosition;
    int mSpeed;
	bool mIsMoving;

protected:
	void OnLButtonDown(POINT position) {
		if (!mShip)
			mShip.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, position.x, position.y, 25, 25);

		SetWindowPos(mShip, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		mCurretnPosition = position;		
	}
	void OnKeyUp(int vk) {		
		mIsMoving = false;
		ShipMoving();
	}
	void OnKeyDown(int vk) {
		if (!mShip)
			return;

		GetClientRect(*this, &mSea);
		GetKeyState(VK_CONTROL) < 0 ? mSpeed = 50 : mSpeed = 5;

		ShipRight();
		ShipLeft();
		ShipDown();
		ShipUp();
		
		ShipMoving();		
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:

	void ShipRight() { 
		if (GetKeyState(VK_RIGHT) < 0 && mCurretnPosition.x < mSea.right - 30)
		{
			mCurretnPosition.x += mSpeed; mIsMoving = true; 
		} 
	}
	void ShipLeft() {
		if (GetKeyState(VK_LEFT) < 0 && mCurretnPosition.x > 0)
		{ 
			mCurretnPosition.x -= mSpeed; mIsMoving = true;
		}
	}
	void ShipDown() {
		if (GetKeyState(VK_DOWN) < 0 && mCurretnPosition.y < mSea.bottom - 30)
		{
			mCurretnPosition.y += mSpeed; mIsMoving = true;
		} 
	}
	void ShipUp() {
		if (GetKeyState(VK_UP) < 0 && mCurretnPosition.y > 25)
		{
			mCurretnPosition.y -= mSpeed; mIsMoving = true;
		} 
	}

	void ShipMoving()
	{
		DWORD style = GetWindowLong(mShip, GWL_STYLE);
		mIsMoving ? SetWindowLong(mShip, GWL_STYLE, style | WS_BORDER) : SetWindowLong(mShip, GWL_STYLE, style& ~WS_BORDER);
		SetWindowPos(mShip, 0, mCurretnPosition.x, mCurretnPosition.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
