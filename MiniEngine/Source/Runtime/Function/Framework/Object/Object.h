#pragma once

#include "Runtime/Function/Framework/Object/ObjectIDAllocator.h"
#include "Runtime/Resource/ResType/Common/Object.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace ME
{
	// GObject : Game Object base class
	class GObject : public std::enable_shared_from_this<GObject>
	{
		typedef std::unordered_set<std::string> TypeNameSet;

	public:
		GObject(GObjectID id) : m_id(id) {}
		virtual ~GObject();

		virtual void Tick(float delta_time);

		bool Load(const ObjectInstanceRes& object_instance_res);


		void SetName(std::string name) { m_name = name; }

	private:
		GObjectID m_id{ k_invalid_gobject_id };
		std::string m_name;
		std::string m_definition_url;

		std::vector<Reflection::ReflectionPtr<Component>> m_components;
	};
}
