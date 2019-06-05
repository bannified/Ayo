#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ayo {
	class AYO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define AYO_CORE_FATAL(...)		::Ayo::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define AYO_CORE_ERROR(...)		::Ayo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AYO_CORE_WARN(...)		::Ayo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AYO_CORE_INFO(...)		::Ayo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AYO_CORE_TRACE(...)		::Ayo::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Core log macros
#define AYO_FATAL(...)			::Ayo::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define AYO_ERROR(...)			::Ayo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AYO_WARN(...)			::Ayo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AYO_INFO(...)			::Ayo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AYO_TRACE(...)			::Ayo::Log::GetCoreLogger()->trace(__VA_ARGS__)
