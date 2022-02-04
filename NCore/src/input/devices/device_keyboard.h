#pragma once

#include "input/input.h"

class CDeviceKeyboard : public Input::IDevice
{
public:
	CDeviceKeyboard(const std::string& _name);
  void Update(Input::TKeyboardData& _data) override;
	void FlushDevice() override;
  //int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam) override;
private:
  Input::TKeyboardData m_data;
};
