#pragma once

#include "core.h"
#include "log.h"

#ifdef NC_ENABLE_ASSERTS
  #define nc_assert(x, ...) { \
		if(!(x)) { \
			log_error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); \
		} \
	} \

#else
  #define nc_assert(x, ...)
#endif

#define nc_fatal(...) { \
	log_error("Fatal error: {0}", __VA_ARGS__); __debugbreak();\
}\

