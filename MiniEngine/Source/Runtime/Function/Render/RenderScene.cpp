#include "RenderScene.h"
#include "Runtime/Function/Render/RenderPass.h"
#include "Runtime/Function/Render/RenderResource.h"


namespace ME
{
	void RenderScene::UpdateVisibleObjects(std::shared_ptr<RenderResource> render_resource, std::shared_ptr<RenderCamera> camera)
	{
		UpdateVisibleObjectsMainCamera(render_resource, camera);
	}


	void RenderScene::SetVisibleNodesReference()
	{
		RenderPass::m_visible_nodes.p_main_camera_visible_mesh_nodes = &m_main_camera_visible_mesh_nodes;
	}

	void RenderScene::UpdateVisibleObjectsMainCamera(std::shared_ptr<RenderResource> render_resource, std::shared_ptr<RenderCamera> camera)
	{
		m_main_camera_visible_mesh_nodes.clear();

		for (const RenderEntity& entity : m_render_entities)
		{
			m_main_camera_visible_mesh_nodes.emplace_back();
			RenderMeshNode& temp_node = m_main_camera_visible_mesh_nodes.back();

			//temp_node.model_matrix

			VulkanMesh& mesh_asset = render_resource->GetEntityMesh(entity);
			temp_node.ref_mesh = &mesh_asset;
			temp_node.enable_vertex_blending = entity.m_enable_vertex_blending;
		}
	}
}
