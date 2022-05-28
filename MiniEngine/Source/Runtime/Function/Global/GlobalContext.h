#pragma once

#include <memory>

namespace ME
{
	class LogSystem;
	class WindowSystem;

	struct EngineInitParams;

	// Manager the lifetime and creation/destruction order of all global system
	class RuntimeGlobalContext
	{
	public:
		// create all global systems and initialize these systems
		void StartSystems(const EngineInitParams& init_params);
		// destroy all global systems
		void ShutdownSystems();

	public:
		std::shared_ptr<LogSystem>		m_logger_system;
		std::shared_ptr<WindowSystem>	m_window_system;
	};

	extern RuntimeGlobalContext g_runtime_global_context;

} // namespace ME
