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
			mShip.Create(*this, WS_VISIBLE|WS_CHILD | WS_BORDER, "X", 1, p.x, p.y, mWidth, mHeight);
		}
		mPosition = p;
		::SetWindowPos(mShip, nullptr, p.x, p.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		if (mShip)
		{
			::SetWindowLong(mShip, GWL_STYLE, GetWindowLong(mShip, GWL_STYLE) & ~WS_BORDER);
			::SetWindowPos(mShip, nullptr, mPosition.x, mPosition.y, NULL, NULL, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOSIZE | SWP_NOZORDER);
		}

	}
	void OnKeyDown(int vk) {
		if (mShip) 
		{
			bool boost= IsKeyPressedAsync(VK_CONTROL);
			int speed = boost ? 10 : 5;
			int offsetX = 0;
			int offsetY = 0;
			switch (vk)
			{
				case VK_UP:
				{
					offsetX = IsKeyPressedAsync(VK_LEFT) ?  -speed : 0;
					offsetX = IsKeyPressedAsync(VK_RIGHT) ? speed : 0;			
					offsetY = -speed;
					Move(offsetX,offsetY);
					break;
				}	
				case VK_DOWN:
				{
					offsetX = IsKeyPressedAsync(VK_LEFT) ? -speed : 0;
					offsetX = IsKeyPressedAsync(VK_RIGHT) ? speed : 0;
					offsetY = speed;
					Move(offsetX, offsetY);
					break;
				}
				case VK_LEFT:
				{
					offsetY = IsKeyPressedAsync(VK_UP) ? -speed : 0;
					offsetY = IsKeyPressedAsync(VK_DOWN) ? speed : 0;
					offsetX = -speed;
					Move(offsetX, offsetY);
					break;
				}
				case VK_RIGHT:
				{
					offsetY = IsKeyPressedAsync(VK_UP) ? -speed : 0;
					offsetY = IsKeyPressedAsync(VK_DOWN) ? speed : 0;
					offsetX = speed;
					Move(offsetX, offsetY);
					break;
				}
			}
			::SetWindowLong(mShip, GWL_STYLE, GetWindowLong(mShip, GWL_STYLE) | WS_BORDER);
			::SetWindowPos(mShip, nullptr, mPosition.x, mPosition.y, NULL, NULL, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
	bool IsKeyPressedAsync(int key)
	{
		// Test high bit - if set, key was down when GetAsyncKeyState was called. 
		return ((1 << 15) & ::GetAsyncKeyState(key)) != 0;
	}
	void Move(const int& offsetX, const int& offsetY)
	{
		RECT rect;
		::GetClientRect(*this, &rect);
		if (offsetX > 0 && mPosition.x + mWidth <= rect.right)
		{
			mPosition.x += offsetX;
			
		}
		else if(mPosition.x > 0 && offsetX < 0)
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

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}
