#pragma once
#include <string>
#include <vector>
#include "events/event.h"

namespace Input
{
  struct KeyboardData;
  struct MouseData;
  struct GamepadData;
  struct RumbleData;

  class Device 
  { 
  public:
    Device(const std::string& _name)
      : m_name(_name)
    {}
    const std::string& GetName() const { return m_name; }

    virtual void Update(KeyboardData& _data) {}
    virtual void Update(MouseData& _data) {}
    virtual void Update(GamepadData& _data) {}
		virtual void FlushDevice() = 0;
    virtual void Feedback(const RumbleData& _data) {}
		//virtual bool OnEvent(NC::Event& _event) = 0;
    /*virtual int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam) {
      return 0;
    }*/


  private:
    std::string m_name;
  };

  using VDevices = std::vector<Device*>;
}
