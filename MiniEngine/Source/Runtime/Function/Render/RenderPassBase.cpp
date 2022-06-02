#include "RenderPassBase.h"

namespace ME
{
	void RenderPassBase::PostInitialize() {}

	void RenderPassBase::PreparePassData(std::shared_ptr<RenderResourceBase> render_resource) {}
	
	void RenderPassBase::InitializeUIRenderBackend(WindowUI* window_ui) {}
} // namespace ME