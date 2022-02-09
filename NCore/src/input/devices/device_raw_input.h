#pragma once

#include "input/device.h"
#include "input/enums.h"

class DeviceRawInput : public Input::Device
{
public:
  DeviceRawInput(const std::string& _name);

  void Update(Input::MouseData& _data) override;
  void Update(Input::KeyboardData& _data) override;
  //int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void FlushDevice() override {}

private:
  bool  m_keys[Input::BT_KEYBOARD_COUNT] = {};
  bool  m_mouse_buttons[Input::BT_MOUSE_COUNT] = {};
  float m_mouse_accum_y = 0.f;
  float m_mouse_accum_x = 0.f;
  int   m_wheel_delta_steps = 0;
};
