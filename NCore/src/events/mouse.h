#pragma once
#include "event.h"

namespace NC {

  struct NC_API MouseMoveEvent : public Event {
		double m_x, m_y;
    MouseMoveEvent(double _x, double _y): m_x(_x), m_y(_y) {}
    std::string ToString() const override { return fmt::format("{}({},{})", std::string(GetName()), m_x, m_y); }
    DECLARE_EVENT(MouseMoveEvent, EventCategoryInput | EventCategoryMouse);
  };

  struct NC_API MouseScrollEvent : public Event {
		double m_scroll_x, m_scroll_y;
    MouseScrollEvent(double _x, double _y) : m_scroll_x(_x), m_scroll_y(_y) {}
    std::string ToString() const override { return fmt::format("{}({},{})", std::string(GetName()), m_scroll_x, m_scroll_y); }
    DECLARE_EVENT(MouseScrollEvent, EventCategoryInput | EventCategoryMouse);
  };

  struct NC_API MouseButtonEvent : public Event {
    int m_button;
    MouseButtonEvent(int _button) : m_button(_button){}
    std::string ToString() const override { return fmt::format("{}({})", std::string(GetName()), m_button); }
    DECLARE_EVENT(MouseButtonEvent, EventCategoryInput | EventCategoryMouse);
  };

  struct NC_API MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(int _button) : MouseButtonEvent(_button) {}
    std::string ToString() const override { return fmt::format("{}({})", std::string(GetName()), m_button); }
    DECLARE_EVENT(MouseButtonPressedEvent, EventCategoryInput | EventCategoryMouse);
  };

  struct NC_API MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(int _button) : MouseButtonEvent(_button) {}
    std::string ToString() const override { return fmt::format("{}({})", std::string(GetName()), m_button); }
    DECLARE_EVENT(MouseButtonReleasedEvent, EventCategoryInput | EventCategoryMouse);
  };
}
