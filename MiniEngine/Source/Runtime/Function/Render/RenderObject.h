#pragma once

#include "Runtime/Core/Math/Matrix4.h"
#include "Runtime/Function/Framework/Object/ObjectIDAllocator.h"

#include <string>
#include <vector>

namespace ME
{
	REFLECTION_TYPE(GameObjectMeshDesc)
	STRUCT(GameObjectMeshDesc, Fields)
	{
		REFLECTION_BODY(GameObjectMeshDesc)
			std::string m_mesh_file;
	};

	REFLECTION_TYPE(GameObjectPartDesc)
	STRUCT(GameObjectPartDesc, Fields)
	{
		REFLECTION_BODY(GameObjectPartDesc)
			GameObjectMeshDesc m_mesh_desc;
	};

	constexpr size_t k_invalid_part_id = std::numeric_limits<size_t>::max();

	class GameObjectDesc
	{
	public:
		GameObjectDesc() : m_go_id(0) {}
		GameObjectDesc(size_t go_id, const std::vector<GameObjectPartDesc>& parts) :
			m_go_id(go_id), m_object_parts(parts)
		{}

		GObjectID GetID() const	{ return m_go_id; }
		const std::vector<GameObjectPartDesc>& GetObjectParts() const { return m_object_parts; }
	private:

		GObjectID m_go_id{ k_invalid_gobject_id };
		std::vector<GameObjectPartDesc> m_object_parts;
	};
}