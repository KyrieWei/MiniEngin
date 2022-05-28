#pragma once

#include "Runtime/Core/Log/LogSystem.h"
#include "Runtime/Function/Global/GlobalContext.h"

#include <chrono>
#include <thread>

#define LOG_HELPER(LOG_LEVEL, ...)\
	g_runtime_global_context.m_logger_system->Log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogSystem::LogLevel::Debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogSystem::LogLevel::Info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogSystem::LogLevel::Warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogSystem::LogLevel::Error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogSystem::LogLevel::Fatal, __VA_ARGS__);
