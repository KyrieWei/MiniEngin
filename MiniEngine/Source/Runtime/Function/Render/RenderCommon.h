#pragma once

#include <glm/glm.hpp>
#include <vulkanmemallocator/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

namespace ME
{
	// mesh
	struct VulkanMesh
	{
		bool enable_vertex_blending;
		uint32_t mesh_vertex_count;
		uint32_t mesh_index_count;
	};

	// nodes
	struct RenderMeshNode
	{
		glm::mat4 model_matrix;
		VulkanMesh* ref_mesh = nullptr;
		uint32_t node_id;
		bool enable_vertex_blending = false;
	};
}