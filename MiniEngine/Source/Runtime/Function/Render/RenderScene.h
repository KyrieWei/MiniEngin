#pragma once
#include "Runtime/Function/Render/RenderEntity.h"
#include "Runtime/Function/Render/RenderCommon.h"

#include <vector>
#include <memory>

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

		// visible objects
		std::vector<RenderMeshNode> m_main_camera_visible_mesh_nodes;

		// update visible objects in each frame
		void UpdateVisibleObjects(std::shared_ptr<RenderResource> render_resource, std::shared_ptr<RenderCamera> camera);

		// set visible nodes ptr in render pass
		void SetVisibleNodesReference();


	private:

		void UpdateVisibleObjectsMainCamera(std::shared_ptr<RenderResource> render_resource,
											std::shared_ptr<RenderCamera> camera);


	};
}

