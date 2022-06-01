#pragma once

#include "Runtime/Function/Render/RenderPipelineBase.h"

namespace ME
{
	class RenderPipeline : public RenderPipelineBase
	{
	public:
		virtual void Initialize(RenderPipelineInitInfo init_info) override final;

		virtual void ForwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource) override final;

		virtual void DeferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource) override final;

	};
}
