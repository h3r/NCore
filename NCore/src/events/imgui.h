#pragma once
#include "events/event.h"

namespace NC {
  struct NC_API ImGuiBegin : public TEvent { DECLARE_EVENT(ImGuiBegin, EventCategoryImGui); };
  struct NC_API ImGuiEnd   : public TEvent { DECLARE_EVENT(ImGuiEnd,   EventCategoryImGui); };
}
