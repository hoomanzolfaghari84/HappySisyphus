#pragma once

#include "Sisyphus/Core/Base.h"
#include "Sisyphus/Core/Log.h"
#include <filesystem>

#ifdef SP_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define SP_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { SP##type##ERROR(msg, __VA_ARGS__); SP_DEBUGBREAK(); } }
	#define SP_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SP_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define SP_INTERNAL_ASSERT_NO_MSG(type, check) SP_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SP_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SP_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SP_INTERNAL_ASSERT_GET_MACRO(...) SP_EXPAND_MACRO( SP_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SP_INTERNAL_ASSERT_WITH_MSG, SP_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define SP_ASSERT(...) SP_EXPAND_MACRO( SP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define SP_CORE_ASSERT(...) SP_EXPAND_MACRO( SP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define SP_ASSERT(...)
	#define SP_CORE_ASSERT(...)
#endif