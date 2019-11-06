#include "nwpwin.h"
#include <algorithm>

class Static : public Window
{
protected:
	std::string ClassName() override
	{
		return "static";
	}
};
class MainWindow : public Window
{
public:
	MainWindow()
		: mWidth(20)
		, mHeight(20)
	{}
protected:
	void OnLButtonDown(POINT p) {
		if (!mShip)
		{
			mShip.Create(*this, mStyle, "X", 1, p.x, p.y, mWidth, mHeight);
		}
		mPosition = p;
		::SetWindowPos(mShip, nullptr, p.x, p.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		if (mShip)
		{
			::SetWindowLong(mShip, GWL_STYLE, GetWindowLong(mShip, GWL_STYLE) & ~WS_BORDER);
			::SetWindowPos(mShip, nullptr, mPosition.x, mPosition.y, NULL, NULL, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE);
		}
		

	}
	void OnKeyDown(int vk) {
		if (mShip) 
		{
			mIsMoving = false;
			bool boost= ::GetAsyncKeyState(VK_CONTROL);
			int speed = boost ? 10 : 5;
			int offsetX = 0;
			int offsetY = 0;
			switch (vk)
			{
				case VK_UP:
				{
					if (CheckState(VK_LEFT)) offsetX = -speed;
					if (CheckState(VK_RIGHT)) offsetX = speed;

					offsetY = -speed;
					Move(offsetX,offsetY);
					break;
				}	
				case VK_DOWN:
				{
					if (CheckState(VK_LEFT)) offsetX = -speed;
					if (CheckState(VK_RIGHT)) offsetX = speed;
	
					
					offsetY = speed;
					Move(offsetX, offsetY);
					break;
				}
				case VK_LEFT:
				{
					if (CheckState(VK_UP)) offsetY = -speed;
					if (CheckState(VK_DOWN)) offsetY = speed;
				
					offsetX = -speed;
					Move(offsetX, offsetY);
					break;
				}
				case VK_RIGHT:
				{
					if (CheckState(VK_UP)) offsetY = -speed;
					if (CheckState(VK_DOWN)) offsetY = speed;

					offsetX = speed;
					Move(offsetX, offsetY);
					break;
				}
			}
			if (mIsMoving)
			{
				::SetWindowLong(mShip, GWL_STYLE, mStyle | WS_BORDER);
			}
			::SetWindowPos(mShip, nullptr, mPosition.x, mPosition.y, NULL, NULL, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	bool CheckState(const int& vk)
	{

		return (::GetKeyState(vk) & (1 << 15));
	}
	void Move(const int& offsetX, const int& offsetY)
	{
		RECT rect;
		::GetClientRect(*this, &rect);
		mIsMoving = true;
		if (offsetX > 0 && mPosition.x + mWidth <= rect.right)
		{
			mPosition.x += offsetX;

		}
		else if (mPosition.x > 0 && offsetX < 0)
		{
			mPosition.x += offsetX;

		}

		if (offsetY > 0 && mPosition.y + mHeight <= rect.bottom)
		{
			mPosition.y += offsetY;
		}
		else if (mPosition.y > 0 && offsetY < 0)
		{
			mPosition.y += offsetY;
		}
	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
	const unsigned int mWidth, mHeight;
	Static mShip;
	POINT  mPosition;
	const DWORD mStyle = WS_CHILD | WS_VISIBLE | SS_CENTER;
	bool mIsMoving;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
