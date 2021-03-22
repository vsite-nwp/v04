#include "nwpwin.h"

class Static : public vsite::nwp::window
{
public:
	std::string class_name() override { return "Static"; }

};

class main_window : public vsite::nwp::window
{
private:
	Static ship;
	POINT point;
	DWORD style = WS_CHILD | WS_VISIBLE | SS_CENTER;


protected:
	void on_left_button_down(POINT p) override { 

		if (!ship)
		{
			ship.create(*this, style, "X", 0, p.x, p.y, 30, 20);
		}
		
		SetWindowPos(ship, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		point = p;
	}
	void on_key_up(int vk) override {
		
		if (ship)
		{
			SetWindowLong(ship, GWL_STYLE, style);
			SetWindowPos(ship, NULL, NULL, NULL, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
		}

	}
	void on_key_down(int vk) override {
		// TODO: if ship exists, move it depending on key and mark as "moving"
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
