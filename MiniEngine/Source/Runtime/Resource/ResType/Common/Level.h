#pragma once

#include "Runtime/Core/Meta/Reflection/Reflection.h"
#include "Runtime/Resource/ResType/Common/Object.h"

namespace ME
{
	REFLECTION_TYPE(LevelRes)
		CLASS(LevelRes, Fields)
	{
		REFLECTION_BODY(LevelRes);

	public:
		float m_gravity{ 9.8f };
		std::string m_character_name;

		std::vector<ObjectInstanceRes> m_objects;
	};
}