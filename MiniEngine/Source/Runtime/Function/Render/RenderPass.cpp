#include "RenderPass.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"

ME::VisibleNodes ME::RenderPass::m_visible_nodes;

namespace ME
{
	void RenderPass::Initialize(const RenderPassInitInfo* init_info)
	{
		m_vulkan_rhi = std::static_pointer_cast<VulkanRHI>(m_rhi);
		
	}

	void RenderPass::Draw() {}

	void RenderPass::PostInitialize() {}

	VkRenderPass RenderPass::GetRenderPass() const { return m_framebuffer.render_pass; }


} // namespace ME
