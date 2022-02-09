#include "ncpch.h"
#include "input/input.h"
#include "input/mapping.h"
#include "input/input_controller.h"

namespace Input {
	class Device;

	void InputController::RegisterDevice(Device* device) {
		if (std::find(m_devices.begin(), m_devices.end(), device) != m_devices.end()){
			log_warn("[WARN!] Registering control device twice in the same controller!");
			return;
		}

		m_devices.push_back(device);

		if (std::find(Input::m_all_devices.begin(), Input::m_all_devices.end(), device) == Input::m_all_devices.end())
			Input::m_all_devices.push_back(device);
	}

	void InputController::AssignMapping(const std::string& _mapping_file) {
		m_mapping.Load(_mapping_file);
	}

	const Button& InputController::operator[](Key _key) const {
		return m_keyboard.GetButton(_key);
	}

	const Button& InputController::operator[](MouseButton _bt) const {
		return m_mouse.GetButton(_bt);
	}

	const Button& InputController::operator[](GamePadButton _bt) const {
		return m_gamepad.GetButton(_bt);
	}

	const Button& InputController::operator[](const std::string& name) const {
		return m_mapping.GetMappedButton(name);
	}

	const Button& InputController::operator[](const ButtonDef& def) const
	{
		switch (def.type)
		{
			case Interface::INTERFACE_KEYBOARD: return (*this)[(Key)def.buttonId];
			case Interface::INTERFACE_MOUSE:		return (*this)[(MouseButton)def.buttonId];
			case Interface::INTERFACE_GAMEPAD:	return (*this)[(GamePadButton)def.buttonId];
			default:return Button::dummy;
		}
	}

	void InputController::Feedback(const RumbleData& data) {
		for (auto& device : m_devices)
			device->Feedback(data);
	}

}
