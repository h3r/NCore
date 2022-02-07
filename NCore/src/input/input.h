#pragma once

#include "input/enums.h"
#include "input/device.h"
#include "input/mapping.h"


#include "interfaces/gamepad.h"
#include "interfaces/keyboard.h"
#include "interfaces/mouse.h"
#include "interfaces/rumble.h"

#include "devices/device_mouse.h"
#include "devices/device_pad_xbox.h"
#include "devices/device_keyboard.h"
#include "devices/device_raw_input.h"

#include "input/input_controller.h"

namespace Input
{
  class CInput {
  public:
		static CInput& _INSTANCE_();
		CInputController& Player(std::string _name);
    CInputController* CreateInputControl(std::string _name);
    bool Start() { return true; }
    void Destroy();
    void Update(float _dt);
    void FlushDevices();
    IDevice* GetDevice(const std::string& _name);

    static void  RegisterButtonDefinitions();
    static const TButtonDef* GetButtonDefinition(const std::string& _name);
    static const std::string& GetButtonName(Interface _type, int _button_id);

    const TButton& operator[](const Key _key) const;
    const TButton& operator[](const MouseButton _bt) const;
    const TButton& operator[](const GamePadButton _bt) const;
    const TButton& operator[](const TButtonDef& _def) const;
    const TButton& operator[](const std::string& _name) const;

    //LRESULT OnOSMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    friend class CInputController;

	private:
		static VDevices m_all_devices;
		static std::map<std::string, CInputController*> m_all_controls;
		static std::map<std::string, TButtonDef> m_button_definitions;

		CInput();
  };

}
#define EngineInput Input::CInput::_INSTANCE_()
