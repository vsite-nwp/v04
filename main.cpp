#include "nwpwin.h"

class Static : public vsite::nwp::window
{
	POINT m_pos;
	int m_step;
public:
	static const int defaultHeight = 20;
	static const int defaultWidth = 20;

	Static()
		: vsite::nwp::window()
		, m_step(20)
		, m_pos{ 0, 0 }
	{
	}

	std::string class_name() override {
		return "Static";
	}

	POINT getCurrPos() const
	{
		return m_pos;
	}

	void setPos(const POINT& p)
	{
		m_pos = p;
	}

	int getStep() const
	{
		return m_step;
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		if (!m_StaticWnd)
			m_StaticWnd.create(*this,
				WS_CHILD | WS_VISIBLE,
				"X", 1,
				p.x, p.y,
				m_StaticWnd.defaultWidth,
				m_StaticWnd.defaultHeight);

		SetWindowPos(m_StaticWnd,0,
			p.x,p.y,
			0, 0,
			SWP_NOSIZE | SWP_NOZORDER);

		m_StaticWnd.setPos(p);
	}
	void on_key_up(int vk) override {
		if (m_StaticWnd) {
			auto wndStyle = GetWindowLong(m_StaticWnd, GWL_STYLE);
			auto currPos = m_StaticWnd.getCurrPos();

			SetWindowLong(m_StaticWnd, GWL_STYLE, wndStyle & ~WS_BORDER);
			SetWindowPos(m_StaticWnd, 0,
				currPos.x, currPos.y,
				0, 0,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}

	}
	void on_key_down(int vk) override {
		if (!m_StaticWnd) return;
		auto currStep = m_StaticWnd.getStep();
		currStep += GetKeyState(VK_CONTROL) < 0 ? 60 : 0;
		auto pos = m_StaticWnd.getCurrPos();
		int next = 0;

		RECT rc; GetClientRect(*this, &rc);

		// handle possible exiting out of rc
		switch (vk)
		{
		case VK_UP:
			next = pos.y - currStep;
			pos.y = next < rc.top ? rc.top : next;
			break;
		case VK_DOWN:
			next = pos.y + currStep + m_StaticWnd.defaultHeight;
			pos.y = min(rc.bottom - m_StaticWnd.defaultHeight, next);
			break;
		case VK_LEFT:
			next = pos.x - currStep;
			pos.x = next < rc.left ? rc.left : next;
			break;
		case VK_RIGHT:
			next = pos.x + currStep + m_StaticWnd.defaultWidth;
			pos.x = min(rc.right - m_StaticWnd.defaultWidth, next);
			break;
		default:
			break;
		}

		auto wndStyle = GetWindowLong(m_StaticWnd, GWL_STYLE);

		SetWindowLong(m_StaticWnd, GWL_STYLE, wndStyle | WS_BORDER);
		SetWindowPos(m_StaticWnd, 0, 
			pos.x, pos.y,
			0, 0,
			SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

		m_StaticWnd.setPos(pos);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	Static m_StaticWnd;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
