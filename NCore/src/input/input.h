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
  class Input {
  public:
		static Input& _INSTANCE_();
		InputController& Player(std::string _name);
    InputController* CreateInputControl(std::string _name);
    bool Start() { return true; }
    void Destroy();
    void Update(float _dt);
    void FlushDevices();
    Device* GetDevice(const std::string& _name);

    static void  RegisterButtonDefinitions();
    static const ButtonDef* GetButtonDefinition(const std::string& _name);
    static const std::string& GetButtonName(Interface _type, int _button_id);

    const Button& operator[](const Key _key) const;
    const Button& operator[](const MouseButton _bt) const;
    const Button& operator[](const GamePadButton _bt) const;
    const Button& operator[](const ButtonDef& _def) const;
    const Button& operator[](const std::string& _name) const;

    //LRESULT OnOSMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    friend class InputController;

	private:
		static VDevices m_all_devices;
		static std::map<std::string, InputController*> m_all_controls;
		static std::map<std::string, ButtonDef> m_button_definitions;

		Input();
  };

}
#define EngineInput Input::Input::_INSTANCE_()
