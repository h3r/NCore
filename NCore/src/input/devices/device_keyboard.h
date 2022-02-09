#pragma once

#include "input/input.h"

class DeviceKeyboard : public Input::Device
{
public:
	DeviceKeyboard(const std::string& _name);
  void Update(Input::KeyboardData& _data) override;
	void FlushDevice() override;
  //int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam) override;
private:
  Input::KeyboardData m_data;
};
