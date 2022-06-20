#pragma once

#include "Runtime/Function/Render/RenderSwapContext.h"
#include "Runtime/Function/Render/RenderType.h"

#include <memory>

namespace ME
{
	class RHI;
	class RenderScene;
	class RenderCamera;

	class RenderResourceBase
	{
	public:

		virtual ~RenderResourceBase() {}

		virtual void UploadGlobalRenderResource(std::shared_ptr<RHI> rhi, LevelResourceDesc level_resource_desc) = 0;


		// TODO: data caching
		RenderMeshData LoadMeshData(const MeshSourceDesc& resource);

	private:
		StaticMeshData LoadStaticMesh(std::string mesh_file);
	};
} // namespace ME


