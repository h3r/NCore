#pragma once

#include "input/device.h"
#include "input/enums.h"

class CDevicePadXbox : public Input::IDevice
{
public:
  CDevicePadXbox(const std::string& _name, unsigned int _controller_id)
    : Input::IDevice(_name)
    , m_controller_id(_controller_id)
  {}

  void Update(Input::TGamepadData& _data) override;
  void Feedback(const Input::TRumbleData& _data) override;
	void FlushDevice() override {}

private:
  unsigned int m_controller_id = 0;
};
