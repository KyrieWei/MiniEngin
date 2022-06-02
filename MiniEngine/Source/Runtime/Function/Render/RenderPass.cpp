#include "RenderPass.h"

namespace ME
{
	void RenderPass::Initialize(const RenderPassInitInfo* init_info)
	{

	}

	void RenderPass::Draw() {}

	void RenderPass::PostInitialize() {}

	VkRenderPass RenderPass::GetRenderPass() const { return m_framebuffer.render_pass; }


} // namespace ME
