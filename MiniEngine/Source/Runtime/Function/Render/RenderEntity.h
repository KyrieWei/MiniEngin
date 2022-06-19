#pragma once
#include "Runtime/Core/Math/Matrix4.h"

#include <cstdint>

namespace ME
{
	class RenderEntity
	{
	public:
		uint32_t m_instance_id{ 0 };
		Matrix4x4 m_model_matrix {Matrix4x4::IDENTITY};

		// mesh
		size_t m_mesh_asset_id{ 0 };   
		bool m_enable_vertex_blending{ false };

	};
}