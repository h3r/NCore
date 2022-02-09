#include "ncpch.h"
#include "input/input.h"
#include "input/input_controller.h"

namespace Input
{
  unsigned int s_current_level = 0;
  const Button Button::dummy;

  VDevices Input::m_all_devices;
  std::map<std::string, InputController*> Input::m_all_controls;
  std::map<std::string, ButtonDef>        Input::m_button_definitions;

	Input& Input::_INSTANCE_() {
		static Input i;
		return i;
	}

  Input::Input() {
    if (m_button_definitions.empty())
      RegisterButtonDefinitions();
  }

	InputController& Input::Player(std::string _name) {
		auto it = m_all_controls.find(_name);
		nc_assert(it != m_all_controls.end(), fmt::format("Input control id not found: {}", _name));
		return *it->second;
	}

  InputController* Input::CreateInputControl(std::string _name) {
    InputController* v = new InputController(_name);
    m_all_controls[_name] = v;
    return v;
  }

  void Input::Destroy() {
    for (auto it : m_all_controls)
      delete it.second;
    
    for (auto* it : m_all_devices)
      delete it;
    
    m_all_controls.clear();
    m_all_devices.clear();
  }

  void Input::Update(float _dt)
  {
    static MouseData mouseData = {};
    static GamepadData gamepadData = {};
    static KeyboardData keyboardData = {};

    for (auto device : m_all_devices) {
      device->Update(keyboardData);
      device->Update(mouseData);
      device->Update(gamepadData);
    }

    for (auto& it : m_all_controls) {
      InputController* control = it.second;
      control->m_mapping.Update(_dt);
      control->m_mouse.Update(mouseData, _dt);
      control->m_gamepad.Update(gamepadData, _dt);
      control->m_keyboard.Update(keyboardData, _dt);
    }

  }

  void Input::FlushDevices() {
    for (auto& device : m_all_devices)
      device->FlushDevice();
  }

  Device* Input::GetDevice(const std::string& _name)
  {
    for (auto& device : m_all_devices) {
      if (device->GetName() == _name)
        return device;
    }
    return nullptr;
  }

  void Input::RegisterButtonDefinitions()
  {
		m_button_definitions.clear();

    static const auto parse_button_definitions = [](const json& _j_data, Interface _type)
    {
      int i = 0;
      for (auto& name : _j_data)
				m_button_definitions[name] = { _type, i++ };
    };

    auto j_data = LoadJson("../data/input/button_definitions.json");

		parse_button_definitions(j_data["mouse"],    INTERFACE_MOUSE);
		parse_button_definitions(j_data["gamepad"],  INTERFACE_GAMEPAD);
		parse_button_definitions(j_data["keyboard"], INTERFACE_KEYBOARD);
  }

  const ButtonDef* Input::GetButtonDefinition(const std::string& _name)
  {
    const auto it = m_button_definitions.find(_name);
    return it != m_button_definitions.end() ? &it->second : nullptr;
  }

  const std::string& Input::GetButtonName(Interface type, int buttonId)
  {
    for (auto& btDef : m_button_definitions) {
      if (btDef.second.type == type && btDef.second.buttonId == buttonId)
        return btDef.first;
    }

    static const std::string dummy;
    return dummy;
  }

  const Button& Input::operator[](Key _key) const {
    if (m_all_controls.empty())
      return Button::dummy;

    auto it = m_all_controls.begin();
		return it->second->m_keyboard.GetButton(_key);
  }

  const Button& Input::operator[](MouseButton _bt) const {
    if (m_all_controls.empty())
      return Button::dummy;

    auto it = m_all_controls.begin();
    return it->second->m_mouse.GetButton(_bt);
  }

  const Button& Input::operator[](GamePadButton _bt) const {
    if (m_all_controls.empty())
      return Button::dummy;

    auto it = m_all_controls.begin();
    return it->second->m_gamepad.GetButton(_bt);
  }

  const Button& Input::operator[](const std::string& _name) const {
    if (m_all_controls.empty())
      return Button::dummy;

    auto it = m_all_controls.begin();
    return it->second->m_mapping.GetMappedButton(_name);
  }

  const Button& Input::operator[](const ButtonDef& def) const
  {
		switch(def.type)
		{
			case Interface::INTERFACE_KEYBOARD:return (*this)[(Key)def.buttonId];
			case Interface::INTERFACE_MOUSE:   return (*this)[(MouseButton)def.buttonId];
			case Interface::INTERFACE_GAMEPAD: return (*this)[(GamePadButton)def.buttonId];
			default: return Button::dummy;
		}
  }

  /*LRESULT Input::OnOSMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    bool processed = false;
    for (auto& device : m_all_devices)
      processed |= device->processWindowMsg(msg, wParam, lParam) ? true : false;

    return processed;
  }*/


}




