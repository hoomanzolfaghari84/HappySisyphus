#pragma once


#include "Sisyphus/Core/Base.h"

// This ignores all warnings raised inside External headers
#ifdef _MSC_VER
    #pragma warning(push, 0)
#endif
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

namespace Sisyphus
{
	class SISYPHUS_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};




	// Core log macros
	#define SIPH_CORE_TRACE(...)    ::Sisyphus::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define SIPH_CORE_INFO(...)     ::Sisyphus::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define SIPH_CORE_WARN(...)     ::Sisyphus::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define SIPH_CORE_ERROR(...)    ::Sisyphus::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define SIPH_CORE_CRITICAL(...) ::Sisyphus::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros		
	#define SIPH_TRACE(...)         ::Sisyphus::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define SIPH_INFO(...)          ::Sisyphus::Log::GetClientLogger()->info(__VA_ARGS__)
	#define SIPH_WARN(...)          ::Sisyphus::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define SIPH_ERROR(...)         ::Sisyphus::Log::GetClientLogger()->error(__VA_ARGS__)
	#define SIPH_CRITICAL(...)      ::Sisyphus::Log::GetClientLogger()->critical(__VA_ARGS__)

}