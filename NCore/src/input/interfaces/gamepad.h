#pragma once

#include "input/button.h"
#include "input/enums.h"

namespace Input
{
  struct GamepadData
  {
    float buttons[BT_GAMEPAD_COUNT];
    bool connected = false;
  };

  class Gamepad
  {
  public:
    void Update(const GamepadData& _data, float _dt) {
      m_connected = _data.connected;
      for (int i = 0; i < BT_GAMEPAD_COUNT; ++i)
        m_buttons[i].update(_data.buttons[i], _dt);
    }
		const Button& GetButton(const GamePadButton& _bt) const {return m_buttons[_bt];}
	private:
    Button m_buttons[BT_GAMEPAD_COUNT];
    bool m_connected = false;
  };
}
