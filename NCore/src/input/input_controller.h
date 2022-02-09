#pragma once

namespace Input {

	class InputController {

	public:
		InputController(std::string _name)
			: m_mapping(*this)
			, m_name(_name)
		{};

		const Mouse& GetMouse()    const { return m_mouse; }
		const Gamepad& GetGamepad()  const { return m_gamepad; }
		const Keyboard& GetKeyboard() const { return m_keyboard; }
		void  Feedback(const RumbleData& _data);

		void RegisterDevice(Device* _device);
		void AssignMapping(const std::string& _mappingFile);
		const Mapping& GetMapping()  const { return m_mapping; }

		const Button& operator[](Key _key) const;
		const Button& operator[](MouseButton _bt) const;
		const Button& operator[](GamePadButton _bt) const;
		const Button& operator[](const ButtonDef& _def) const;
		const Button& operator[](const std::string& _name) const;

		friend class Input;
	protected:
		Mouse    m_mouse;
		Gamepad  m_gamepad;
		Keyboard m_keyboard;
		Mapping  m_mapping;

	private:
		std::string m_name;
		VDevices m_devices;
	};

}
