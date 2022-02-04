#pragma once
#include <string>
#include <vector>
#include "events/event.h"

namespace Input
{
  struct TKeyboardData;
  struct TMouseData;
  struct TGamepadData;
  struct TRumbleData;

  class IDevice 
  { 
  public:
    IDevice(const std::string& _name)
      : m_name(_name)
    {}
    const std::string& GetName() const { return m_name; }

    virtual void Update(TKeyboardData& _data) {}
    virtual void Update(TMouseData& _data) {}
    virtual void Update(TGamepadData& _data) {}
		virtual void FlushDevice() = 0;
    virtual void Feedback(const TRumbleData& _data) {}
		//virtual bool OnEvent(NC::TEvent& _event) = 0;
    /*virtual int processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam) {
      return 0;
    }*/


  private:
    std::string m_name;
  };

  using VDevices = std::vector<IDevice*>;
}
