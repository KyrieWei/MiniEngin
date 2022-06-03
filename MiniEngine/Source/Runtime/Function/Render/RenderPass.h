#pragma once
#include "Runtime/Function/Render/RenderPassBase.h"

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace ME
{
	class VulkanRHI;

	enum
	{
		_main_camera_pass_gbuffer_a				= 0,
		_main_camera_pass_backup_buffer_odd		= 3,
		_main_camera_pass_backup_buffer_even	= 4,
		_main_camera_pass_attachment_count		= 9,
	};

	enum
	{
		_main_camera_subpass_basepass = 0,
		_main_camera_subpass_ui,
		_main_camera_subpass_count
	};

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

