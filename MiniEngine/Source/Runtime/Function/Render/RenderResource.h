#pragma once
#include "Runtime/Function/Render/RenderResourceBase.h"



namespace ME
{
	class RHI;
	class RenderPassBase;
	
	class RenderResource : public RenderResourceBase
	{
	public:
		virtual void UploadGlobalRenderResource(std::shared_ptr<RHI> rhi,
												LevelResourceDesc	 level_resource_desc) override final;
	};


} // namespace ME

