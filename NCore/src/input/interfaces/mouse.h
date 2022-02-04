#pragma once

#include "input/enums.h"
#include "input/button.h"

namespace Input
{
  struct TMouseData
  {
    bool buttons[BT_MOUSE_COUNT];
		float pos_x;
		float pos_y;
		float delta_x;
		float delta_y;
    float scroll = 0.f;
		std::pair<float, float> GetDelta()		const { return std::make_pair(pos_x, pos_y); }
		std::pair<float, float> GetPosition() const { return std::make_pair(pos_x, pos_y); }
  };

  class CMouse
  {
  public:
		void Update(const TMouseData& _data, float _dt) {
			auto [dx, dy] = _data.GetDelta();
			m_pos_x = dx;
			m_pos_y = dy;
			m_scroll = _data.scroll;

			for (int i = 0; i < BT_MOUSE_COUNT; ++i)
				m_buttons[i].update(_data.buttons[i] ? 1.f : 0.f, _dt);
		}
		const TButton& GetButton(const MouseButton _bt) const {	return m_buttons[_bt]; }
    std::pair<float, float> GetDelta()    const { return std::make_pair(m_pos_x, m_pos_y); }
		std::pair<float, float> GetPosition() const { return std::make_pair(m_pos_x, m_pos_y); }
	
	private:
		float m_pos_x;
		float m_pos_y;
    float m_scroll = 0.f;
    TButton m_buttons[BT_MOUSE_COUNT];
  };

}
