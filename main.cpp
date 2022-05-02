#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship

class STATIC : public vsite::nwp::window 
{ 
	public:std::string class_name() override { return "STATIC"; } 
};


class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location
		location = p;
		if (!ship) {
			ship.create(*this, style, "X", 0, p.x, p.y, 50, 50);
		}
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {
		// TODO: mark ship (if exists) as "not moving"
		DWORD style = GetWindowLong(ship, GWL_STYLE);
		style &= ~WS_BORDER;
		if (ship) {
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}
	}
	void on_key_down(int vk) override {
		// TODO: if ship exists, move it depending on key and mark as "moving"
		RECT rc; GetClientRect(*this,&rc);
		int speed = GetAsyncKeyState(VK_CONTROL) ? 30:15 ;

		
			switch (vk) {
			case VK_LEFT:
				location.x -= speed;
				if (location.x < 0)
					location.x = rc.right;
				break;
				//location.x = max(0, location.x - speed);
			case VK_RIGHT: 
				location.x += speed; 
				if (location.x > rc.right) 
				
					location.x = 0; 
				break;
			case VK_UP: 
				location.y -= speed; 
				if (location.y < 0) 
				
					location.y = rc.bottom;
				break;
			case VK_DOWN: 
				location.y += speed;  
				if (location.y > rc.bottom)
				
					location.y = 0;
				break;
			}
		SetWindowLong(ship, GWL_STYLE, style | WS_BORDER);
		SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	STATIC ship;
	POINT location;
	DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
