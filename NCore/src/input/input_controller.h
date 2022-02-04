#pragma once;

namespace Input {

	class CInputController {

	public:
		CInputController(std::string _name)
			: m_mapping(*this)
			, m_name(_name)
		{};

		const CMouse& Mouse()    const { return m_mouse; }
		const CGamepad& Gamepad()  const { return m_gamepad; }
		const CKeyboard& Keyboard() const { return m_keyboard; }
		void  Feedback(const TRumbleData& _data);

		void RegisterDevice(IDevice* _device);
		void AssignMapping(const std::string& _mappingFile);
		const CMapping& Mapping()  const { return m_mapping; }

		const TButton& operator[](Key _key) const;
		const TButton& operator[](MouseButton _bt) const;
		const TButton& operator[](GamePadButton _bt) const;
		const TButton& operator[](const TButtonDef& _def) const;
		const TButton& operator[](const std::string& _name) const;

		friend class CInput;
	protected:
		CMouse    m_mouse;
		CGamepad  m_gamepad;
		CKeyboard m_keyboard;
		CMapping  m_mapping;

	private:
		std::string m_name;
		VDevices m_devices;
	};

}
