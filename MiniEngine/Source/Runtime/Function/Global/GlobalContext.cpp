#include "GlobalContext.h"

#include "Runtime/Core/Log/LogSystem.h"
#include "Runtime/Resource/ConfigManager/ConfigManager.h"
#include "Runtime/Function/Render/WindowSystem.h"
#include "Runtime/Function/Render/RenderSystem.h"

namespace ME
{
	RuntimeGlobalContext g_runtime_global_context;

	void RuntimeGlobalContext::StartSystems(const std::string& config_file_path)
	{

		m_config_manager = std::make_shared<ConfigManager>();
		m_config_manager->Initialize(config_file_path);

		m_logger_system = std::make_shared<LogSystem>();

		m_window_system = std::make_shared<WindowSystem>();
		WindowCreateInfo window_create_info;
		m_window_system->Initialize(window_create_info);

		m_render_system = std::make_shared<RenderSystem>();
		RenderSystemInitInfo render_init_info;
		render_init_info.window_system = m_window_system;
		m_render_system->Initialize(render_init_info);
	}

	void RuntimeGlobalContext::ShutdownSystems()
	{
		m_render_system.reset();
		
		m_window_system.reset();

		m_logger_system.reset();

		m_config_manager.reset();
	}
}