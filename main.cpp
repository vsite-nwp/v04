#include "nwpwin.h"



class ship :public vsite::nwp::window {
	virtual std::string class_name() { return "STATIC"; }


};

class main_window : public vsite::nwp::window
{
	ship brod;
	POINT position;
	const int shipHeight = 20;
	const int shipWidth = 20;
protected:
	void on_left_button_down(POINT p) override { 
	
		if(!brod)
		brod.create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 1, p.x,p.y,shipHeight,shipWidth);
		position = p;
		
	
		SetWindowPos(brod, 0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	void on_key_up(int vk) override {
		
		if (brod) {
			SetWindowLong(brod, GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER);
			SetWindowPos(brod, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
		}

	}
	void on_key_down(int vk) override {
	
		int brod_brzina = GetAsyncKeyState(VK_CONTROL) ? 20 : 10;
		RECT rect;
		GetClientRect(*this, &rect);

		switch (vk) {
		case VK_LEFT:
			position.x = max(position.x - brod_brzina, rect.left);
			break;
		case VK_UP:
			position.y = max(position.y - brod_brzina, rect.top);
			break;
		case VK_RIGHT:
			position.x = min(position.x + brod_brzina, rect.right - shipWidth);
			break;
		case VK_DOWN:
			position.y = min(position.y + brod_brzina, rect.bottom - shipHeight);
			break;
		default:
			return;
		}

		SetWindowLong(brod,GWL_STYLE, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER);
		SetWindowPos(brod, 0, position.x, position.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
		
	

		 
			
			
		
		
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
