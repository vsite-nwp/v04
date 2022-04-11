#include "nwpwin.h"

using namespace std;

// TODO: prepare class ("STATIC") for a ship

POINT location;

class STATIC : public vsite::nwp::window {

public:
	string class_name() override {
		return "static";
	}

};

class main_window : public vsite::nwp::window
{
	STATIC ship;

protected:
	void on_left_button_down(POINT p) override {   //WM_LBUTTONDOWN
		// TODO: create ship if it doesn't exist yet
		// TODO: change current location

		location = p;
		
		if (!ship) {
			ship.create(*this, WS_VISIBLE | WS_CHILD | SS_CENTER, "X", 0, location.x, location.y, 20, 20);
		}

		SetWindowPos(ship, 0, location.x, location.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void on_key_up(int vk) override {  //WM_KEYUP
		// TODO: mark ship (if exists) as "not moving"
	}
	void on_key_down(int vk) override {  //WM_KEYDOWN
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




/*
* POINT location;
* Static ship;
* 
* void on:left_button(POINT p) overrirde{
* location = p:
* if(ship){
* ship.create();
* SetWindowPos(ship,.....);
* 
* void on_key_up(int vk)override{
* DWORD style = getWindowsLong(ship, GWl_STYLE);  - krajeci polja da ne izletimo izvan
* //remove WS_BORDER bit
* SetWindowLong(ship, GWL_STYLE, style);
* }
* void on_key_down(int vk) override{
* RECT rc; GetClientReact(&rc);
* int speed = getAyncKeyStatic(VK_CTRL) ? ;
* 
* 
* switch(vk){
* case VK_LEFT: location x -= spedd;
* case VK_RIGHT : local.x=;
* case VK_UP : location.y=;
* case VK_DOWN : location.y=;
* default return;
* 
* DWORD style = GetWindowsLong(ship, GWL_STYLE);
* //add WS_BORDER bit
* SetWindowsLong(ship,GWL_STYLE, style);
* SetWindowPos(ship,..,);//
* 
*/