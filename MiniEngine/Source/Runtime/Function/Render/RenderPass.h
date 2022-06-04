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
		_main_camera_pass_gbuffer_a						= 0,
		_main_camera_pass_gbuffer_b						= 1,
		_main_camera_pass_gbuffer_c						= 2,
		_main_camera_pass_backup_buffer_odd				= 3,
		_main_camera_pass_backup_buffer_even			= 4,
		_main_camera_pass_post_process_buffer_odd		= 5,
		_main_camera_pass_post_process_buffer_even		= 6,
		_main_camera_pass_depth							= 7,
		_main_camera_pas_swap_chain_image				= 8,
		_main_camera_pass_custom_attachment_count		= 5,
		_main_camera_pass_post_process_attachment_count = 2,
		_main_camera_pass_attachment_count				= 9,
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

		struct FrameBufferAttachment
		{
			VkImage			image;
			VkDeviceMemory	mem;
			VkImageView		view;
			VkFormat		format;
		};

		struct Framebuffer
		{
			int				width;
			int				height;
			VkFramebuffer	framebuffer;
			VkRenderPass	render_pass;

			std::vector<FrameBufferAttachment> attachments;
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

