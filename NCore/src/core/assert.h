#pragma once

#include "core.h"
#include "log.h"
#include <filesystem>

#ifdef HZ_ENABLE_ASSERTS
  #define nc_assert(x, ...) {if(!x){ log_error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
  #define nc_assert(x, ...)
#endif