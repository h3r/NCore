#pragma once

#include <memory>

#include "utils/platformdetector.h"


#ifdef NC_PLATFORM_WINDOWS
#include <Windows.h>
#ifdef NC_DYNAMIC_LINK
#ifdef NC_BUILD_DLL
#define NC_API __declspec(dllexport)
#else
#define NC_API __declspec(dllimport)
#endif
#else
#define NC_API
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

namespace NC {

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}

#include "utils/log.h"
#include "utils/uuid.h"
#include "utils/assert.h"
#include "utils/utils.h"
