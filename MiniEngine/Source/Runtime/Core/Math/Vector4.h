#pragma once
#include "Runtime/Core/Meta/Reflection/Reflection.h"

namespace ME
{
	REFLECTION_TYPE(Vector4)
	CLASS(Vector4, Fields)
	{
		REFLECTION_BODY(Vector4);

	public:
		float x{ 0.f }, y{ 0.f }, z{ 0.f }, w{ 0.f };

	public:
		Vector4() = default;

	};
}
