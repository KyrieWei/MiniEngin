#include "RenderResource.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"

#include <stdexcept>

namespace ME
{
	void RenderResource::UploadGlobalRenderResource(std::shared_ptr<RHI> rhi, LevelResourceDesc level_resource_desc)
	{

	}

	VulkanMesh& RenderResource::GetEntityMesh(RenderEntity entity)
	{
		size_t asset_id = entity.m_mesh_asset_id;

		auto it = m_vulkan_meshes.find(asset_id);
		if (it != m_vulkan_meshes.end())
		{
			return it->second;
		}
		else
		{
			throw std::runtime_error("Failed to get entity mesh!");
		}
	}

	VulkanMesh& RenderResource::GetOrCreateVulkanMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data)
	{
		size_t asset_id = entity.m_mesh_asset_id;

		auto it = m_vulkan_meshes.find(asset_id);
		if (it != m_vulkan_meshes.end())
		{
			return it->second;
		}
		else
		{
			VulkanMesh temp;
			auto res = m_vulkan_meshes.insert(std::make_pair(asset_id, std::move(temp)));
			assert(res.second);

			uint32_t index_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_index_buffer->m_size);
			void* index_buffer_data = mesh_data.m_static_mesh_data.m_index_buffer->m_data;

			uint32_t vertex_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_size);
			MeshVertexDataDefinition* vertex_buffer_data = reinterpret_cast<MeshVertexDataDefinition*>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_data);

			VulkanMesh& now_mesh = res.first->second;
			if (false)
			{

			}
			else
			{
				UpdateMeshData(rhi, 
							false, 
							index_buffer_size, 
							index_buffer_data, 
							vertex_buffer_size,
							vertex_buffer_data,
							now_mesh);
			}

			return now_mesh;
		}
	}

	void RenderResource::UpdateMeshData(std::shared_ptr<RHI> rhi,
										bool enable_vertex_blending,
										uint32_t index_buffer_size,
										void* index_buffer_data,
										uint32_t vertex_buffer_size,
										struct MeshVertexDataDefinition const* vertex_buffer_data,
										VulkanMesh& now_mesh)
	{
		now_mesh.enable_vertex_blending = enable_vertex_blending;
		assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));
		now_mesh.mesh_vertex_count = vertex_buffer_size / sizeof(MeshVertexDataDefinition);
		UpdateVertexBuffer(rhi,
			enable_vertex_blending,
			vertex_buffer_size,
			vertex_buffer_data,
			index_buffer_size,
			reinterpret_cast<uint16_t*>(index_buffer_data),
			now_mesh);

		assert(0 == (index_buffer_size % sizeof(uint16_t)));
		now_mesh.mesh_index_count = index_buffer_size / sizeof(uint16_t);
		UpdateIndexBuffer(rhi, index_buffer_size, index_buffer_data, now_mesh);
	}

	void RenderResource::UpdateVertexBuffer(std::shared_ptr<RHI> rhi,
											bool enable_vertex_blending,
											uint32_t vertex_buffer_size,
											struct MeshVertexDataDefinition const* vertex_buffer_data,
											uint32_t index_buffer_size,
											uint16_t* index_buffer_data,
											VulkanMesh& now_mesh)
	{
		VulkanRHI* vulkan_context = static_cast<VulkanRHI*>(rhi.get());

		if (enable_vertex_blending)
		{

		}
		else
		{
			assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));
			uint32_t vertex_count = vertex_buffer_size / sizeof(MeshVertexDataDefinition);

			//VkDeviceSize vertex_position_buffer_size = 
		}
	}

	void RenderResource::UpdateIndexBuffer(std::shared_ptr<RHI> rhi,
											uint32_t index_buffer_size,
											void* index_buffer_data,
											VulkanMesh& now_mesh)
	{

	}
}