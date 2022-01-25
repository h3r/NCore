#pragma once
#include "event.h"

namespace NC {
  
  struct NC_API WindowResizeEvent : public Event { 
    unsigned int m_width, m_height;
    WindowResizeEvent() {}
    WindowResizeEvent(unsigned int _width, unsigned int _height) : m_width(_width), m_height(_height) {}
    std::string ToString() const override { return fmt::format("{} ({},{})", std::string(GetName()), m_width, m_height); }
    DECLARE_EVENT(WindowResizeEvent, EventCategoryApplication);
  };
  struct NC_API WindowCloseEvent  : public Event { DECLARE_EVENT(WindowCloseEvent,  EventCategoryApplication); };
  struct NC_API AppTickEvent      : public Event { DECLARE_EVENT(AppTickEvent,      EventCategoryApplication); };
  struct NC_API AppUpdateEvent    : public Event { DECLARE_EVENT(AppUpdateEvent,    EventCategoryApplication); };
  struct NC_API AppRenderEvent    : public Event { DECLARE_EVENT(AppRenderEvent,    EventCategoryApplication); };
}
