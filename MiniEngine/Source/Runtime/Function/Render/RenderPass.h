#pragma once
#include "Runtime/Function/Render/RenderPassBase.h"

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace ME
{
	class VulkanRHI;

	class RenderPass : public RenderPassBase
	{
	public:

		struct Framebuffer
		{
			int width;
			int height;
			VkFramebuffer framebuffer;
			VkRenderPass render_pass;
			
		};

		std::shared_ptr<VulkanRHI> m_vulkan_rhi{ nullptr };
		
		Framebuffer m_framebuffer;

		void Initialize(const RenderPassInitInfo* init_info) override;
		void PostInitialize() override;

		virtual void Draw();

		virtual VkRenderPass GetRenderPass() const;
		//virtual std::vector<VkImageView> GetFrameBufferImageViews() const;
		//virtual std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts() const;

		
	};
} // namespace ME

