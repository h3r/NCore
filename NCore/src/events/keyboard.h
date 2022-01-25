#pragma once
#include "event.h"

namespace NC {
  
  struct NC_API KeyEvent : public Event { 
    int m_keycode;
    KeyEvent(int _keycode) : m_keycode(_keycode){}
    //virtual std::string ToString() const override { return fmt::format("{}({})", std::string(GetName()), m_keycode); }
    DECLARE_EVENT(KeyEvent, EventCategoryInput | EventCategoryKeyboard);
  };

  struct NC_API KeyPressedEvent : public KeyEvent { 
    int m_repeat;
    KeyPressedEvent(int _keycode, int _repeat) : KeyEvent(_keycode) , m_repeat(_repeat){}
    std::string ToString() const override { return fmt::format("{}({}):{}", std::string(GetName()), m_keycode, m_repeat); }
    DECLARE_EVENT(KeyPressedEvent, EventCategoryInput | EventCategoryKeyboard);
  };

  struct NC_API KeyReleasedEvent : public KeyEvent { 
    KeyReleasedEvent(int _keycode) : KeyEvent(_keycode){}
    std::string ToString() const override { return fmt::format("{}({})", std::string(GetName()), m_keycode); }
    DECLARE_EVENT(KeyPressedEvent, EventCategoryInput | EventCategoryKeyboard);
  };

}
