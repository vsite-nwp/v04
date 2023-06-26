#include "nwpwin.h"

class Static : public vsite::nwp::window
{
	POINT m_pos;
public:
	static const int defaultHeight = 20;
	static const int defaultWidth = 20;

	std::string class_name() override {
		return "Static";
	}

	Static()
		: vsite::nwp::window()
		, m_pos{ 0, 0 }
	{
	}

	POINT getCurrPos() const
	{
		return m_pos;
	}

	void setPos(const POINT& p)
	{
		m_pos = p;
	}
	};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		if (!m_StaticWnd)
			m_StaticWnd.create(*this,
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				"X", 1,
				p.x, p.y,
				m_StaticWnd.defaultWidth,
				m_StaticWnd.defaultHeight);

		// just draw Static
		SetWindowPos(m_StaticWnd,0, // ignored
			p.x,p.y, // new pos
			0, 0, // ignored (noresize)
			SWP_NOSIZE | SWP_NOZORDER);

		m_StaticWnd.setPos(p);
	}
	void on_key_up(int vk) override {
		if (m_StaticWnd) {
			auto wndStyle = GetWindowLong(m_StaticWnd, GWL_STYLE);

			// remove border
			SetWindowLong(m_StaticWnd, GWL_STYLE, wndStyle & ~WS_BORDER);

			// redraw
			SetWindowPos(m_StaticWnd, 0, // ignored by SWP_NOZORDER
				0, 0, // ignored by SWP_NOMOVE
				0, 0, // ignored by SWP_NOSIZE
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}

	}
	void on_key_down(int vk) override {
		if (!m_StaticWnd) return;

		auto step = m_StaticWnd.defaultWidth;
		step += GetKeyState(VK_CONTROL) < 0 ? 60 : 0;
		auto pos = m_StaticWnd.getCurrPos();
		bool moving{ false };

		RECT rc; GetClientRect(*this, &rc);

		// handle possible exiting out of rc (pos is top left so we might drop out at down and right)
		switch (vk)
		{
		case VK_UP:
			pos.y = max(rc.top, pos.y - step);
			moving = true;
			break;
		case VK_DOWN:
			pos.y = min(rc.bottom - m_StaticWnd.defaultHeight, pos.y + step);
			moving = true;
			break;
		case VK_LEFT:
			pos.x = max(rc.left, pos.x - step);
			moving = true;
			break;
		case VK_RIGHT:
			pos.x = min(rc.right - m_StaticWnd.defaultWidth, pos.x + step);
			moving = true;
			break;
		default:
			break;
		}

		if (moving) {
			auto wndStyle = GetWindowLong(m_StaticWnd, GWL_STYLE);
			SetWindowLong(m_StaticWnd, GWL_STYLE, wndStyle | WS_BORDER);
			SetWindowPos(m_StaticWnd, 0, // ignored by SWP_NOZORDER
				pos.x, pos.y, // new pos
				0, 0, // ignored by SWP_NOSIZE
				SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);

			m_StaticWnd.setPos(pos);
		}
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
