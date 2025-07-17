#pragma once

#include <memory>

//#include "Sisyphus/Core/PlatformDetection.h"


//#ifdef SP_DEBUG
//#if defined(SP_PLATFORM_WINDOWS)
//#define SP_DEBUGBREAK() __debugbreak()
//#elif defined(SP_PLATFORM_LINUX)
//#include <signal.h>
//#define SP_DEBUGBREAK() raise(SIGTRAP)
//#else
//#error "Platform doesn't support debugbreak yet!"
//#endif
//#define SP_ENABLE_ASSERTS
//#else
//#define SP_DEBUGBREAK()
//#endif
//
//#define SP_EXPAND_MACRO(x) x
//#define SP_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)


 // --- Macros For Dynamic Linking --
#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SISYPHUS_API __declspec(dllexport)
	#else
		#define SISYPHUS_API __declspec(dllimport)
	#endif // SP_BUILD_DLL
#else
	#error Sisyphus only supports Windows!
#endif // SP_PLATFORM_WINDOWS

#define SP_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }



#ifdef SP_ENABLE_ASSERTS
#define SP_ASSERT(x, ...) {if(!(x)) {SIPH_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak();} }
#define SP_CORE_ASSERT(x, ...) {if(!(x)) {SIPH_CORE_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak();} }
#else
#define SP_ASSERT(x, ...)
#define SP_CORE_ASSERT(x, ...)
#endif



//namespace Sisyphus {
//
//	template<typename T>
//	using Scope = std::unique_ptr<T>;
//	template<typename T, typename ... Args>
//	constexpr Scope<T> CreateScope(Args&& ... args)
//	{
//		return std::make_unique<T>(std::forward<Args>(args)...);
//	}
//
//	template<typename T>
//	using Ref = std::shared_ptr<T>;
//	template<typename T, typename ... Args>
//	constexpr Ref<T> CreateRef(Args&& ... args)
//	{
//		return std::make_shared<T>(std::forward<Args>(args)...);
//	}
//
//}

#include "Sisyphus/Core/Log.h"
//#include "Sisyphus/Core/Assert.h"