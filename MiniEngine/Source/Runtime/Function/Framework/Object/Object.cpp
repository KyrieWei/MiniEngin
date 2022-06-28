#include "Object.h"
#include "Runtime/Function/Global/GlobalContext.h"
#include "Runtime/Resource/AssetManager/AssetManager.h"

namespace ME
{
	GObject::~GObject()
	{

	}

	bool GObject::Load(const ObjectInstanceRes& object_instance_res)
	{
		// clear old components
		m_components.clear();

		SetName(object_instance_res.m_name);

		// load object instanced components
		m_components = object_instance_res.m_instanced_components;
		for (auto component : m_components)
		{
			if (component)
			{
				//component->PostLoadResource(weak_from_this());
			}
		}

		// load object definition components
		m_definition_url = object_instance_res.m_definition;

		ObjectDefinitionRes definition_res;

		const bool is_loaded_success = g_runtime_global_context.m_asset_manager->LoadAsset(m_definition_url, definition_res);
		if (!is_loaded_success)
		{
			return false;
		}

		for (auto loaded_component : definition_res.m_components)
		{
			m_components.push_back(loaded_component);
		}

		return true;
	}

	void GObject::Tick(float delta_time)
	{

	}
}
