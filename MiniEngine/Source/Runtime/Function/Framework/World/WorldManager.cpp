#include "WorldManager.h"
#include "Runtime/Function/Global/GlobalContext.h"
#include "Runtime/Resource/ConfigManager/ConfigManager.h"
#include "Runtime/Resource/AssetManager/AssetManager.h"

#include "Runtime/Function/Framework/Level/Level.h"
#include "Runtime/Core/Base/Macro.h"

namespace ME
{
	WorldManager::~WorldManager() { Clear(); }

	void WorldManager::Initialize()
	{
		m_is_world_loaded = false;
		m_current_world_url = g_runtime_global_context.m_config_manager->GetDefaultWorldUrl();
	}

	void WorldManager::Clear()
	{
		// unload all loaded levels
		for (auto level_pair : m_loaded_levels)
		{
			level_pair.second->Unload();
		}
		m_loaded_levels.clear();

		m_current_active_level.reset();

		// clear world
		m_current_world_resource.reset();
		m_current_world_url.clear();
		m_is_world_loaded = false;
	}

	void WorldManager::Tick(float delta_time)
	{
		if (!m_is_world_loaded)
		{
			LoadWorld(m_current_world_url);
		}

		// tick the active level
		std::shared_ptr<Level> active_level = m_current_active_level.lock();
		if (active_level)
		{
			active_level->Tick(delta_time);
		}
	}

	bool WorldManager::LoadWorld(const std::string& world_url)
	{
		LOG_INFO("Loading world: {}", world_url);

		WorldRes world_res;
		const bool is_world_load_success = g_runtime_global_context.m_asset_manager->LoadAsset(world_url, world_res);
		if (!is_world_load_success)
		{
			return false;
		}

		m_current_world_resource = std::make_shared<WorldRes>(world_res);

		const bool is_level_load_success = LoadLevel(world_res.m_default_level_url);
		if (!is_level_load_success)
		{
			return false;
		}

		// set the default level to be active level
		auto iter = m_loaded_levels.find(world_res.m_default_level_url);
		assert(iter != m_loaded_levels.end());

		m_current_active_level = iter->second;

		m_is_world_loaded = true;

		LOG_INFO("World load successed!");
		return true;
	}

	bool WorldManager::LoadLevel(const std::string& level_url)
	{
		std::shared_ptr<Level> level = std::make_shared<Level>();

		// set current level temporary
		m_current_active_level = level;

		const bool is_level_load_success = level->Load(level_url);
		if (!is_level_load_success)
		{
			return false;
		}

		m_loaded_levels.emplace(level_url, level);

		return true;
	}
}