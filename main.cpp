#include "nwpwin.h"

class Static : public Window {

public: std::string ClassName() override {

	return "static";
}
};

class MainWindow : public Window
{
	RECT mSea;
	Static mShip;
	POINT mCurrentPosition;
	int mSpeed;
	// constants
	const DWORD mStyle = WS_VISIBLE | WS_CHILD | SS_CENTER;
	const int mBoardWidth = 25;
	const int mBoardHeight = 25;
protected:
	void OnLButtonDown(POINT position) {
		if (!mShip)
		{
			mShip.Create(*this, mStyle, "x", 0, position.x, position.y, mBoardWidth, mBoardHeight);
		}

		SetWindowPos(mShip, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		mCurrentPosition = position;
	}
	void OnKeyUp(int vk) {
		if (mShip)
		{
			::SetWindowLong(mShip, GWL_STYLE, GetWindowLong(mShip, GWL_STYLE) & ~WS_BORDER);
			::SetWindowPos(mShip, nullptr, mCurrentPosition.x, mCurrentPosition.y, NULL, NULL, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE);
		}
	}
	void OnKeyDown(int vk) {
		if (!mShip)
			return;

		GetClientRect(*this, &mSea);
		GetKeyState(VK_CONTROL) < 0 ? mSpeed = 50 : mSpeed = 5;
		switch (vk)
		{
		case VK_UP:
		{
			ShipUp();
			break;
		}
		case VK_DOWN:
		{
			ShipDown();
			break;
		}
		case VK_LEFT:
		{
			ShipLeft();
			break;

		}
		case VK_RIGHT:
		{
			ShipRight();
			break;
		}
		}
		DWORD style = GetWindowLong(mShip, GWL_STYLE);
		SetWindowLong(mShip, GWL_STYLE, style | WS_BORDER);
		::SetWindowPos(mShip, nullptr, mCurrentPosition.x, mCurrentPosition.y, NULL, NULL, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
	}

	void OnDestroy() {
		::PostQuitMessage(0);
	}
private:

	void ShipRight() {
		if (mCurrentPosition.x < mSea.right - mBoardWidth)
		{
			mCurrentPosition.x += mSpeed;
		}
	}
	void ShipLeft() {
		if (mCurrentPosition.x > 0)
		{
			mCurrentPosition.x -= mSpeed;
		}
	}
	void ShipDown() {
		if (mCurrentPosition.y < mSea.bottom - mBoardHeight)
		{
			mCurrentPosition.y += mSpeed;
		}
	}
	void ShipUp() {
		if (mCurrentPosition.y > mBoardHeight)
		{
			mCurrentPosition.y -= mSpeed;
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
