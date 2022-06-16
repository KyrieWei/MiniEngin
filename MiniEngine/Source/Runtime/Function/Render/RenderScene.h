#pragma once
#include "Runtime/Function/Render/RenderEntity.h"

#include <vector>

namespace ME
{
	class RenderResource;
	class RenderCamera;

	class RenderScene
	{
	public:
		//light

		// render entities
		std::vector<RenderEntity> m_render_entities;
	};
}

