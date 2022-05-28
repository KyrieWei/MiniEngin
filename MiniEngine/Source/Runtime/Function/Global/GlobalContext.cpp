#include "GlobalContext.h"

#include "Runtime/Core/Log/LogSystem.h"
#include "Runtime/Function/Render/WindowSystem.h"

namespace ME
{
	RuntimeGlobalContext g_runtime_global_context;

	void RuntimeGlobalContext::StartSystems(const EngineInitParams& init_params)
	{
		m_logger_system = std::make_shared<LogSystem>();

		m_window_system = std::make_shared<WindowSystem>();
		WindowCreateInfo window_create_info;
		m_window_system->Initialize(window_create_info);
	}

	void RuntimeGlobalContext::ShutdownSystems()
	{
		m_logger_system.reset();

		m_window_system.reset();
	}
}