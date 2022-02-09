#pragma once


namespace Input
{
	struct Button {
		float m_value = 0.f;
		float m_previous_value = 0.f;
		float m_time_pressed = 0.f;
		inline bool isPressed()    const { return m_value != 0.f; }
		inline bool wasPressed()   const { return m_previous_value != 0.f; }
		inline bool justPressed()  const { return m_previous_value == 0.f && m_value != 0.f; }
		inline bool justReleased() const { return m_previous_value != 0.f && m_value == 0.f; }
		inline bool justChanged()  const { return m_previous_value != m_value; }
		operator bool() const { return isPressed(); }
		void update(float _new_value, float _dt)
		{
			m_previous_value = m_value;
			m_value = _new_value;

			if (justPressed())
				m_time_pressed = 0.f;
			else if (isPressed())
				m_time_pressed += _dt;
		}
    static const Button dummy;
	};
}
