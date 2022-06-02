#pragma once

#include "Runtime/Function/Render/RenderPassBase.h"

#include <memory>
#include <vector>

namespace ME
{
	class RHI;
	class RenderResourceBase;
	class WindowUI;

	struct RenderPipelineInitInfo
	{
		std::shared_ptr<RenderResourceBase> render_resource;
	};

	class RenderPipelineBase
	{
		friend class RenderSystem;

	public:
		virtual ~RenderPipelineBase() {}

		virtual void Initialize(RenderPipelineInitInfo init_info) = 0;
		virtual void PreparePassData(std::shared_ptr<RenderResourceBase> render_resource);
		virtual void ForwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource);
		virtual void DeferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource);

	protected:
		std::shared_ptr<RHI> m_rhi;

		std::shared_ptr<RenderPassBase> m_ui_pass;
	};
}

