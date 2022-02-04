#pragma once

#include "input/device.h"
#include "input/enums.h"

class CDeviceMouse : public Input::IDevice
{
public:
  CDeviceMouse(const std::string& _name);
  void Update(Input::TMouseData& _data) override;
	void FlushDevice() override;
  //int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam) override;

private:
  void StartRawInputData();
  bool m_buttons[Input::BT_MOUSE_COUNT] = {};
  int m_pos_x = 0;
  int m_pos_y = 0;
  int m_scroll = 0;
  int m_delta_x = 0;
  int m_delta_y = 0;
};
