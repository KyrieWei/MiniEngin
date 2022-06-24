#pragma once
#include "Runtime/Function/Framework/Object/ObjectIDAllocator.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace ME
{
	class Character;
	class GObject;
	class ObjectInstanceRes;
	
	using LevelObjectsMap = std::unordered_map<GObjectID, std::shared_ptr<GObject>>;

	// The main class to manage all game objects
	class Level
	{
	public:
		virtual ~Level();

		bool Load(const std::string& level_res_url);
		void Unload();

		bool Save();

		void Tick(float delta_time);

		GObjectID CreateObject(const ObjectInstanceRes& object_instance_res);

	protected:
		void Clear();

		bool m_is_loaded{ false };
		std::string m_level_res_url;

		// all game objects in this level, key: object id, value: object instance
		LevelObjectsMap m_gobjects;

	};
}
