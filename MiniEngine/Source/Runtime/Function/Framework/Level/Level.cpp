#include "Level.h"
#include "Runtime/Core/Base/Macro.h"

#include "Runtime/Resource/AssetManager/AssetManager.h"
#include "Runtime/Resource/ResType/Common/Level.h"

#include "Runtime/Engine.h"
#include "Runtime/Function/Framework/Object/Object.h"

#include <limits>

namespace ME
{
	Level::~Level() { Clear(); }

	void Level::Clear()
	{
		m_gobjects.clear();

	}

	GObjectID Level::CreateObject(const ObjectInstanceRes& object_instance_res)
	{
		GObjectID object_id = ObjectIDAllocator::Alloc();
		assert(object_id != k_invalid_gobject_id);

		std::shared_ptr<GObject> gobject;
		try
		{
			gobject = std::make_shared<GObject>(object_id);
		}
		catch (const std::exception&)
		{
			LOG_FATAL("Cannot allocate memory for new gobject!");
		}

		bool is_loaded = gobject->Load(object_instance_res);
		if (is_loaded)
		{
			m_gobjects.emplace(object_id, gobject);
		}
		else
		{
			LOG_ERROR("Loading object " + object_instance_res.m_name + " failed!");
			return k_invalid_gobject_id;
		}

		return object_id;

	}

	bool Level::Load(const std::string& level_res_url)
	{
		LOG_INFO("Loading level: {}", level_res_url);

		m_level_res_url = level_res_url;

		LevelRes level_res;
		const bool is_load_success = g_runtime_global_context.m_asset_manager->LoadAsset(level_res_url, level_res);
		if (!is_load_success)
		{
			return false;
		}

		for (const ObjectInstanceRes& object_instance_res : level_res.m_objects)
		{
			CreateObject(object_instance_res);
		}


		m_is_loaded = true;
		
		LOG_INFO("Level load succeed");

		return true;
	}

	void Level::Unload()
	{
		Clear();
		LOG_INFO("Unload level: {}", m_level_res_url);
	}

	bool Level::Save()
	{
		LOG_INFO("Saving level: {}", m_level_res_url);

		return true;
	}

	void Level::Tick(float delta_time)
	{
		if (!m_is_loaded)
		{
			return;
		}


	}
}
