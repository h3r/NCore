#include "ncpch.h"
#include "input/input.h"
#include "input/mapping.h"
#include "input/input_controller.h"

namespace Input {
	class IDevice;

	void CInputController::RegisterDevice(IDevice* device) {
		if (std::find(m_devices.begin(), m_devices.end(), device) != m_devices.end()){
			log_warn("[WARN!] Registering control device twice in the same controller!");
			return;
		}

		m_devices.push_back(device);

		if (std::find(CInput::m_all_devices.begin(), CInput::m_all_devices.end(), device) == CInput::m_all_devices.end())
			CInput::m_all_devices.push_back(device);
	}

	void CInputController::AssignMapping(const std::string& _mapping_file) {
		m_mapping.Load(_mapping_file);
	}

	const TButton& CInputController::operator[](Key _key) const {
		return m_keyboard.GetButton(_key);
	}

	const TButton& CInputController::operator[](MouseButton _bt) const {
		return m_mouse.GetButton(_bt);
	}

	const TButton& CInputController::operator[](GamePadButton _bt) const {
		return m_gamepad.GetButton(_bt);
	}

	const TButton& CInputController::operator[](const std::string& name) const {
		return m_mapping.GetMappedButton(name);
	}

	const TButton& CInputController::operator[](const TButtonDef& def) const
	{
		switch (def.type)
		{
			case Interface::INTERFACE_KEYBOARD: return (*this)[(Key)def.buttonId];
			case Interface::INTERFACE_MOUSE:		return (*this)[(MouseButton)def.buttonId];
			case Interface::INTERFACE_GAMEPAD:	return (*this)[(GamePadButton)def.buttonId];
			default:return TButton::dummy;
		}
	}

	void CInputController::Feedback(const TRumbleData& data) {
		for (auto& device : m_devices)
			device->Feedback(data);
	}

}
