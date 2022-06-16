#pragma once

#include "Runtime/Core/Math/Math.h"
#include "Runtime/Core/Meta/Reflection/Reflection.h"

#include <cassert>

namespace ME
{
	class Matrix3x3;
	class Vector3;

	REFLECTION_TYPE(Quaternion)
	CLASS(Quaternion, Fields)
	{
		REFLECTION_BODY(Quaternion);

	public:
		float w{ 1.f }, x{ 0.f }, y{ 0.f }, z{ 0.f };

	public:

		Quaternion() = default;
	};
}

