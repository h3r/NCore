#pragma once
#include "events/event.h"

namespace NC {
  struct NC_API ImGuiBegin : public Event { DECLARE_EVENT(ImGuiBegin, EventCategoryImGui); };
  struct NC_API ImGuiEnd   : public Event { DECLARE_EVENT(ImGuiEnd,   EventCategoryImGui); };
}
