#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace BHive
{
	class BHive_API Log
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

//Core Log Macros
#define BH_CORE_TRACE(...)	:: BHive::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BH_CORE_INFO(...)	:: BHive::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BH_CORE_WARN(...)	:: BHive::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BH_CORE_ERROR(...)	:: BHive::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BH_CORE_FATAL(...)	:: BHive::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define BH_TRACE(...)	:: BHive::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BH_INFO(...)	:: BHive::Log::GetClientLogger()->info(__VA_ARGS__)
#define BH_WARN(...)	:: BHive::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BH_ERROR(...)	:: BHive::Log::GetClientLogger()->error(__VA_ARGS__)
#define BH_FATAL(...)	:: BHive::Log::GetClientLogger()->fatal(__VA_ARGS__)