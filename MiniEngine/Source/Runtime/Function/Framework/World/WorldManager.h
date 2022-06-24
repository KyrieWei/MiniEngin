#pragma once
#include "Runtime/Resource/ResType/Common/World.h"

#include <filesystem>
#include <string>

namespace ME
{
	class Level;
	

	class WorldManager
	{
	public:
		virtual ~WorldManager();

		void Initialize();
		void Clear();

		void Tick(float delta_time);
		std::weak_ptr<Level> GetCurrentActiveLevel() const { return m_current_active_level; }

	private:
		bool LoadWorld(const std::string& world_url);
		bool LoadLevel(const std::string& level_url);

		bool						m_is_world_loaded{ false };
		std::string					m_current_world_url;
		std::shared_ptr<WorldRes>	m_current_world_resource;

		// all loaded levels, key: level_url, value: level instance
		std::unordered_map<std::string, std::shared_ptr<Level>> m_loaded_levels;

		// active level, currently we just support one active level
		std::weak_ptr<Level> m_current_active_level;
	};
}

