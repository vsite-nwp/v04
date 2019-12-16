#include "nwpwin.h"
#define SHIPY 25
#define SHIPX 25

class Static : public Window{
public:
	std::string ClassName() override
	{
		return "static";
	}
};


class MainWindow : public Window
{
protected:
	void OnLButtonDown(POINT p) {

		cursor = p;

		if (!ship)
		{
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER , "X", NULL, p.x, p.y, SHIPX, SHIPY);
		}
		else
		{
			SetWindowPos(ship, NULL, p.x, p.y, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
		}

	}
	void OnKeyUp(int vk) {

		SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER );
		SetWindowPos(ship, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE);

	}
	void OnKeyDown(int vk) {

		RECT window;
		int speedMode = 1;


		if (ship)
		{

			GetClientRect(*this, &window);

			if (GetKeyState(VK_CONTROL) & 0x8000)
				speedMode = 5;

			switch(vk)
			{
			/* Movement action */
			case VK_UP:
				cursor.y = max( cursor.y - speedMode, window.top);
				break;

			case VK_DOWN:
				cursor.y = min( cursor.y + speedMode, window.bottom - SHIPY);
				break;

			case VK_LEFT:
				cursor.x = max( cursor.x - speedMode, window.left);
				break;

			case VK_RIGHT:
				cursor.x = min( cursor.x + speedMode, window.right -SHIPX);
				break;
			}

			SetWindowLong(ship, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
			SetWindowPos(ship, NULL, cursor.x, cursor.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED  );

		}

	}
	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:

	Static ship;
	POINT cursor;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	
	return app.Run();
}
