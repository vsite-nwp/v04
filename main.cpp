#include "nwpwin.h"

// TODO: prepare class ("STATIC") for a ship
class ship :public vsite::nwp::window {
	virtual std::string class_name() { return "STATIC"; }


};

class main_window : public vsite::nwp::window
{
	ship brod;
	POINT position;
protected:
	void on_left_button_down(POINT p) override { 
		// TODO: create ship if it doesn't exist yet
		if(!brod)
		brod.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "X", 1, p.x,p.y,50,50);
		position = p;
		
		// TODO: change current location
		SetWindowPos(brod, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	void on_key_up(int vk) override {
		// TODO: mark ship (if exists) as "not moving"
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
