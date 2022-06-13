#pragma once

#include "Runtime/Function/Render/RenderPass.h"
#include "Runtime/Function/Render/Passes/UIPass.h"

namespace ME
{
	class RenderResourceBase;

	class MainCameraPass : public RenderPass
	{
	public:

		void Initialize(const RenderPassInitInfo* init_info) override final;

		void PreparePassData(std::shared_ptr<RenderResourceBase> render_resource) override final;

		void Draw(UIPass& ui_pass, uint32_t current_swapchain_image_index);

		void DrawForward(UIPass& ui_pass, uint32_t current_swapchain_image_index);

	private:
		void SetupAttachments();
		void SetupRenderPass();
		void SetupPipelines();
		void SetupDescriptorSet();
		void SetupFramebufferDescriptorSet();
		void SetupSwapchainFramebuffers();

		void SetupCommandBuffers();

	private:
		std::vector<VkFramebuffer> m_swapchain_framebuffers;
	};
}