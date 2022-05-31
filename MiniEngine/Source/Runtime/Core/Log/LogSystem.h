#pragma once
#include <spdlog/spdlog.h>
#include <cstdint>
#include <stdexcept>

namespace ME
{

	class LogSystem final
	{
	public:
		enum class LogLevel : uint8_t
		{
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};

	public:
		LogSystem();
		~LogSystem();

		template<typename... TARGS>
		void Log(LogLevel level, TARGS&&... args)
		{
			switch (level)
			{
			case LogLevel::Debug:
				m_logger->debug(std::forward<TARGS>(args)...);
				break;
			case LogLevel::Info:
				m_logger->info(std::forward<TARGS>(args)...);
				break;
			case LogLevel::Warn:
				m_logger->warn(std::forward<TARGS>(args)...);
				break;
			case LogLevel::Error:
				m_logger->error(std::forward<TARGS>(args)...);
				break;
			case LogLevel::Fatal:
				m_logger->critical(std::forward<TARGS>(args)...);
				FatalCallback(std::forward<TARGS>(args)...);
				break;
			default:
				break;
			}
		}

		template<typename... TARGS>
		void FatalCallback(TARGS&&... args)
		{
			const std::string format_str = fmt::format(std::forward<TARGS>(args)...);
			throw std::runtime_error(format_str);
		}

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};

} // namespace ME
