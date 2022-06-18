#pragma once
#include "Runtime/Core/Math/MathHeaders.h"

#include <mutex>
#include <vector>

namespace ME
{
	enum class RenderCameraType : int
	{
		Editor,
		Motor
	};

	class RenderCamera
	{
	public:
		RenderCameraType m_current_camera_type{ RenderCameraType::Editor };

		static const Vector3 X, Y, Z;

		Vector3		m_position{ 0.0f, 0.0f, 0.0f };

		float		m_znear{ 1000.0f };
		float		m_zfar{ 0.1f };
		Vector3		m_up_axis{ Z };

		static constexpr float MIN_FOV{ 10.0f };
		static constexpr float MAX_FOV{ 89.0f };
		
	};

	inline const Vector3 RenderCamera::X = { 1.0f, 0.0f, 0.0f };
	inline const Vector3 RenderCamera::Y = { 0.0f, 1.0f, 0.0f };
	inline const Vector3 RenderCamera::Z = { 0.0f, 0.0f, 1.0f };
	
}

