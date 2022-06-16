#pragma once
#include "Runtime/Core/Meta/Reflection/Reflection.h"

namespace ME
{
	REFLECTION_TYPE(Vector2)
	CLASS(Vector2, Fields)
	{
		REFLECTION_BODY(Vector2);

	public:
		float x{ 0.f }, y{ 0.f };

	public:
		Vector2() = default;

	};
}
