#pragma once
#include <cstdint>
#include <memory>

namespace ME
{
	enum class RENDER_PIPELINE_TYPE : uint8_t
	{
		FORWARD_PIPELINE = 0,
		DEFERRED_PIPELINE,
		PIPELINE_TYPE_COUNT
	};

	class BufferData
	{
	public:
		size_t m_size{ 0 };
		void* m_data{ nullptr };

		BufferData() = delete;
		BufferData(size_t size)
		{
			m_size = size;
			m_data = malloc(size);
		}
		~BufferData()
		{
			if (m_data)
			{
				free(m_data);
			}
		}

		bool IsValid() const { return m_data != nullptr; }
	};

	struct MeshVertexDataDefinition
	{
		float x, y, z;		// position
		float nx, ny, nz;	// normal
		float tx, ty, tz;	// tangent
		float u, v;			// UV coordinates
	};

	struct StaticMeshData
	{
		std::shared_ptr<BufferData> m_vertex_buffer;
		std::shared_ptr<BufferData> m_index_buffer;
	};

	struct RenderMeshData
	{
		StaticMeshData m_static_mesh_data;
		//std::shared_ptr<BufferData> m_skeleton_binding_buffer;
	};
}
