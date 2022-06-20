#include "RenderResourceBase.h"
#include "Runtime/Resource/AssetManager/AssetManager.h"
#include "Runtime/Core/Math/MathHeaders.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

namespace ME
{
	RenderMeshData RenderResourceBase::LoadMeshData(const MeshSourceDesc& source)
	{
		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
		assert(asset_manager);

		RenderMeshData ret;

		if (std::filesystem::path(source.m_mesh_file).extension() == ".obj")
		{
			ret.m_static_mesh_data = LoadStaticMesh(source.m_mesh_file);
		}
		else if(std::filesystem::path(source.m_mesh_file).extension() == ".json")
		{
			//std::shared_ptr<
		}

		return ret;
	}

	StaticMeshData RenderResourceBase::LoadStaticMesh(std::string mesh_file)
	{
		StaticMeshData mesh_data;

		tinyobj::ObjReader reader;
		tinyobj::ObjReaderConfig reader_config;
		reader_config.vertex_color = false;

		if (!reader.ParseFromFile(mesh_file, reader_config))
		{
			if (!reader.Error().empty())
			{
				LOG_ERROR("Load Mesh {} failed, error: {}", mesh_file, reader.Error());
			}
			assert(0);
		}

		if (!reader.Warning().empty())
		{
			LOG_WARN("Load Mesh {} warning, warning : {}", mesh_file, reader.Warning());
		}

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		std::vector<MeshVertexDataDefinition> mesh_vertices;

		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				bool with_normal = true;
				bool with_texcoord = true;
				
				Vector3 vertex[3];
				Vector3 normal[3];
				Vector2 uv[3];

				// only deals with triangles faces
				if (fv != 3)
				{
					continue;
				}

				// expanding vertex data is not efficient and is for testing purposes only
				for (size_t v = 0; v < fv; v++)
				{
					auto idx = shapes[s].mesh.indices[index_offset + v];
					auto vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					auto vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					auto vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

					vertex[v].x = static_cast<float>(vx);
					vertex[v].y = static_cast<float>(vy);
					vertex[v].z = static_cast<float>(vz);

					if (idx.normal_index >= 0)
					{
						auto nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
						auto ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
						auto nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

						normal[v].x = static_cast<float>(nx);
						normal[v].y = static_cast<float>(ny);
						normal[v].z = static_cast<float>(nz);
					}
					else
					{
						with_normal = false;
					}

					if (idx.texcoord_index >= 0)
					{
						auto tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						auto ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

						uv[v].x = static_cast<float>(tx);
						uv[v].y = static_cast<float>(ty);
					}
					else
					{
						with_texcoord = false;
					}
				}

				index_offset += fv;  

				if (!with_normal)
				{
					Vector3 v0 = vertex[1] - vertex[2];
					Vector3 v1 = vertex[2] - vertex[1];
					normal[0] = v0.crossProduct(v1).normalizedCopy();
					normal[1] = normal[0];
					normal[2] = normal[0];
				}

				if (!with_texcoord)
				{
					uv[0] = Vector2(0.5f, 0.5f);
					uv[1] = Vector2(0.5f, 0.5f);
					uv[2] = Vector2(0.5f, 0.5f);
				}

				Vector3 tangent{ 1, 0, 0 };
				{
					Vector3 edge1 = vertex[1] - vertex[0];
					Vector3 edge2 = vertex[2] - vertex[1];
					Vector2 deltaUV1 = uv[1] - uv[0];
					Vector2 deltaUV2 = uv[2] - uv[1];

					auto divide = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
					if (divide >= 0.0f && divide < 0.000001f)
					{
						divide = 0.000001f;
					}
					else if (divide < 0.0f && divide > -0.000001f)
					{
						divide = -0.000001f;
					}

					float df = 1.0f / divide;
					tangent.x = df * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					tangent.y = df * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					tangent.z = df * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
					tangent = (tangent).normalizedCopy();
				}

				for (size_t i = 0; i < 3; i++)
				{
					MeshVertexDataDefinition mesh_vert{};

					mesh_vert.x = vertex[i].x;
					mesh_vert.y = vertex[i].y;
					mesh_vert.z = vertex[i].z;

					mesh_vert.nx = normal[i].x;
					mesh_vert.ny = normal[i].y;
					mesh_vert.nz = normal[i].z;

					mesh_vert.u = uv[i].x;
					mesh_vert.v = uv[i].y;

					mesh_vert.tx = tangent.x;
					mesh_vert.ty = tangent.y;
					mesh_vert.tz = tangent.z;

					mesh_vertices.push_back(mesh_vert);
				}
			}
		}

		uint32_t stride = sizeof(MeshVertexDataDefinition);
		mesh_data.m_vertex_buffer = std::make_shared<BufferData>(mesh_vertices.size() * stride);
		mesh_data.m_vertex_buffer = std::make_shared<BufferData>(mesh_vertices.size() * sizeof(uint16_t));

		assert(mesh_vertices.size() <= std::numeric_limits<uint16_t>::max());

		uint16_t* indices = (uint16_t*)mesh_data.m_index_buffer->m_data;
		for (size_t i = 0; i < mesh_vertices.size(); i++)
		{
			((MeshVertexDataDefinition*)mesh_data.m_vertex_buffer->m_data)[i] = mesh_vertices[i];
			indices[i] = static_cast<uint16_t>(i);
		}

		return mesh_data;
	}
}