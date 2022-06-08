#include "RenderPassBase.h"

namespace ME
{
	void RenderPassBase::PostInitialize() {}

	void RenderPassBase::SetCommonInfo(RenderPassCommonInfo common_info)
	{
		m_rhi = common_info.rhi;
		m_render_resource = common_info.render_resource;
	}

	void RenderPassBase::PreparePassData(std::shared_ptr<RenderResourceBase> render_resource) {}
	
	void RenderPassBase::InitializeUIRenderBackend(WindowUI* window_ui) {}
} // namespace ME