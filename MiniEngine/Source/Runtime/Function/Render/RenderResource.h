#pragma once
#include "Runtime/Function/Render/RenderResourceBase.h"
#include "Runtime/Function/Render/RenderEntity.h"
#include "Runtime/Function/Render/RenderCommon.h"
#include "Runtime/Function/Render/RenderType.h"

#include <map>

namespace ME
{
	class RHI;
	class RenderPassBase;
	
	class RenderResource : public RenderResourceBase
	{
	public:
		virtual void UploadGlobalRenderResource(std::shared_ptr<RHI> rhi,
												LevelResourceDesc	 level_resource_desc) override final;


		VulkanMesh& GetEntityMesh(RenderEntity entity);

		// cached mesh and material
		std::map<size_t, VulkanMesh> m_vulkan_meshes;

	private:
		void CreateAndMapStorageBuffer(std::shared_ptr<RHI> rhi);
		VulkanMesh& GetOrCreateVulkanMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data);

		void UpdateMeshData(std::shared_ptr<RHI> rhi,
							bool enable_vertex_blending,
							uint32_t index_buffer_size,
							void* index_buffer_data,
							uint32_t vertex_buffer_size,
							struct MeshVertexDataDefinition const* vertex_buffer_data,
							VulkanMesh& now_mesh);

		void UpdateVertexBuffer(std::shared_ptr<RHI> rhi,
								bool enable_vertex_blending,
								uint32_t vertex_buffer_size,
								struct MeshVertexDataDefinition const* vertex_buffer_data,
								uint32_t index_buffer_size,
								uint16_t* index_buffer_data,
								VulkanMesh& now_mesh);

		void UpdateIndexBuffer(std::shared_ptr<RHI> rhi,
								uint32_t index_buffer_size,
								void* index_buffer_data,
								VulkanMesh& now_mesh);
	};


} // namespace ME

