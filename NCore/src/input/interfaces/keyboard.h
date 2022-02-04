#pragma once

#include "input/button.h"
#include "input/enums.h"

namespace Input
{
  struct TKeyboardData
  {
    bool keys[BT_KEYBOARD_COUNT];
  };

  class CKeyboard
  {
  public:
    void Update(const TKeyboardData& _data, float _dt)
    {
      for (int i = 0; i < BT_KEYBOARD_COUNT; ++i)
        m_buttons[i].update(_data.keys[i] ? 1.f : 0.f, _dt);
    }

		const TButton& GetButton(const Key& _key) const{return m_buttons[_key];}
		
	private:
    TButton m_buttons[BT_KEYBOARD_COUNT];
  };
}
