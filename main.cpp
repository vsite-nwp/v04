#include "nwpwin.h"

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
			ship.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER , "X", NULL, p.x, p.y, 25, 25);
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
		POINT mw;
		

		if (ship)
		{

			GetClientRect(ship, &window);
			mw.x = window.right;
			mw.y = window.bottom;

			/* Multiple speed modes */
			switch (vk)
			{
			case VK_CONTROL:
				speedMode = 5;
				break;

			case VK_MENU:
				speedMode = 10;
				break;

			case VK_SHIFT:
				speedMode *= (-1);
				break;

			/* speed up and speed down */
			case VK_OEM_PLUS:
				++speedMode;
				break;

			case VK_OEM_MINUS:
				--speedMode;
				break;
			}

			/* Movement action */
			switch (vk) 
			{

			case VK_UP:
				cursor.y -= speedMode;
				break;

			case VK_DOWN:
				cursor.y += speedMode;
				break;

			case VK_LEFT:
				cursor.x -= speedMode;
				break;

			case VK_RIGHT:
				cursor.x += speedMode;
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
	int speedMode = 1;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	
	return app.Run();
}
