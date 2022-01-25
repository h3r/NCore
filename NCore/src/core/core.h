#pragma once

#include <memory>

#include "platformdetector.h"


#ifdef NC_PLATFORM_WINDOWS
  #include <Windows.h>
  #ifdef NC_BUILD_DLL
    #define NC_API __declspec(dllexport)
  #else
    #define NC_API __declspec(dllimport)
  #endif
#else
  #error ONLY supported in windows
#endif


#ifdef NC_DEBUG
	#if defined(NC_PLATFORM_WINDOWS)
		#define NC_DEBUGBREAK() __debugbreak()
	#elif defined(NC_PLATFORM_LINUX)
		#include <signal.h>
		#define NC_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define NC_ENABLE_ASSERTS
#else
	#define NC_DEBUGBREAK()
#endif



#define BIT(x) (1 << x)
#define BIND(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "log.h"
#include "assert.h"