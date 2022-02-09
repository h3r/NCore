#pragma once

#include "input/button.h"
#include "input/enums.h"

namespace Input
{
  struct KeyboardData
  {
    bool keys[BT_KEYBOARD_COUNT];
  };

  class Keyboard
  {
  public:
    void Update(const KeyboardData& _data, float _dt)
    {
      for (int i = 0; i < BT_KEYBOARD_COUNT; ++i)
        m_buttons[i].update(_data.keys[i] ? 1.f : 0.f, _dt);
    }

		const Button& GetButton(const Key& _key) const{return m_buttons[_key];}
		
	private:
    Button m_buttons[BT_KEYBOARD_COUNT];
  };
}
