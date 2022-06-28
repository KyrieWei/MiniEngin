#pragma once

#include <memory>
#include <string>

namespace ME
{
	class LogSystem;
	class ConfigManager;
	class AssetManager;
	class WorldManager;
	class WindowSystem;
	class RenderSystem;

	// Manager the lifetime and creation/destruction order of all global system
	class RuntimeGlobalContext
	{
	public:
		// create all global systems and initialize these systems
		void StartSystems(const std::string& config_file_path);
		// destroy all global systems
		void ShutdownSystems();

	public:
		std::shared_ptr<LogSystem>		m_logger_system;
		std::shared_ptr<AssetManager>	m_asset_manager;
		std::shared_ptr<ConfigManager>	m_config_manager;
		std::shared_ptr<WorldManager>	m_world_manager;
		std::shared_ptr<WindowSystem>	m_window_system;
		std::shared_ptr<RenderSystem>	m_render_system;
	};

	extern RuntimeGlobalContext g_runtime_global_context;

} // namespace ME
