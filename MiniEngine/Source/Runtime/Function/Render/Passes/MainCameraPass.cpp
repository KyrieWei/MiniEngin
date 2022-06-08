#include "MainCameraPass.h"

#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"

#include <stdexcept>

namespace ME
{
	void MainCameraPass::Initialize(const RenderPassInitInfo* init_info)
	{
		RenderPass::Initialize(nullptr);

		SetupAttachments();
		SetupRenderPass();
	}

	void MainCameraPass::PreparePassData(std::shared_ptr<RenderResourceBase> render_resource)
	{

	}

	void MainCameraPass::SetupAttachments()
	{
		m_framebuffer.attachments.resize(_main_camera_pass_custom_attachment_count +
										 _main_camera_pass_post_process_attachment_count);

		m_framebuffer.attachments[_main_camera_pass_gbuffer_a].format			= VK_FORMAT_R8G8B8A8_UNORM;
		m_framebuffer.attachments[_main_camera_pass_gbuffer_b].format			= VK_FORMAT_R8G8B8A8_UNORM;
		m_framebuffer.attachments[_main_camera_pass_gbuffer_c].format			= VK_FORMAT_R8G8B8A8_SRGB;
		m_framebuffer.attachments[_main_camera_pass_backup_buffer_odd].format	= VK_FORMAT_R16G16B16A16_SFLOAT;
		m_framebuffer.attachments[_main_camera_pass_backup_buffer_even].format	= VK_FORMAT_R16G16B16A16_SFLOAT;

		for (int i = 0; i < _main_camera_pass_custom_attachment_count; ++i)
		{
			
		}
	}
	
	void MainCameraPass::SetupRenderPass()
	{
		/*
		VkAttachmentDescription attachments[_main_camera_pass_attachment_count] = {};

		VkAttachmentDescription& backup_odd_color_attachment_description = attachments[_main_camera_pass_backup_buffer_odd];
		backup_odd_color_attachment_description.format			= m_framebuffer.attachments[_main_camera_pass_backup_buffer_odd].format;
		backup_odd_color_attachment_description.samples			= VK_SAMPLE_COUNT_1_BIT;
		backup_odd_color_attachment_description.loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
		backup_odd_color_attachment_description.storeOp			= VK_ATTACHMENT_STORE_OP_DONT_CARE;
		backup_odd_color_attachment_description.stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		backup_odd_color_attachment_description.stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
		backup_odd_color_attachment_description.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
		backup_odd_color_attachment_description.finalLayout		= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		VkAttachmentDescription& backup_even_color_attachment_description = attachments[_main_camera_pass_backup_buffer_even];
		backup_even_color_attachment_description.format			= m_framebuffer.attachments[_main_camera_pass_backup_buffer_even].format;
		backup_even_color_attachment_description.samples		= VK_SAMPLE_COUNT_1_BIT;
		backup_even_color_attachment_description.loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
		backup_even_color_attachment_description.storeOp		= VK_ATTACHMENT_STORE_OP_DONT_CARE;
		backup_even_color_attachment_description.stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		backup_even_color_attachment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		backup_even_color_attachment_description.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
		backup_even_color_attachment_description.finalLayout	= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		VkSubpassDescription subpasses[_main_camera_subpass_count] = {};

		VkAttachmentReference ui_pass_color_attachment_reference{};
		ui_pass_color_attachment_reference.attachment = &backup_odd_color_attachment_description - attachments;
		ui_pass_color_attachment_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		uint32_t ui_pass_preserve_attachment = &backup_even_color_attachment_description - attachments;

		VkSubpassDescription& ui_pass = subpasses[_main_camera_subpass_ui];
		ui_pass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		ui_pass.inputAttachmentCount = 0;
		ui_pass.pInputAttachments = NULL;
		ui_pass.colorAttachmentCount = 1;
		ui_pass.pColorAttachments = &ui_pass_color_attachment_reference;
		ui_pass.pDepthStencilAttachment = NULL;
		ui_pass.preserveAttachmentCount = 1;
		ui_pass.pPreserveAttachments = &ui_pass_preserve_attachment;

		VkSubpassDependency dependencies[8] = {};

		VkRenderPassCreateInfo renderpass_create_info{};
		renderpass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpass_create_info.attachmentCount = (sizeof(attachments) / sizeof(attachments[0]));
		renderpass_create_info.pAttachments = attachments;
		renderpass_create_info.subpassCount = (sizeof(subpasses) / sizeof(subpasses[0]));
		renderpass_create_info.pSubpasses = subpasses;
		renderpass_create_info.dependencyCount = (sizeof(dependencies) / sizeof(dependencies[0]));
		renderpass_create_info.pDependencies = dependencies;
		*/

		VkAttachmentDescription ColorAttachment{};
		ColorAttachment.format = m_vulkan_rhi->m_swapchain_image_format;
		ColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		ColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		ColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		ColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		ColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		ColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference ColorAttachmentRef{};
		ColorAttachmentRef.attachment = 0;
		ColorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &ColorAttachmentRef;

		VkRenderPassCreateInfo RenderPassInfo{};
		RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassInfo.attachmentCount = 1;
		RenderPassInfo.pAttachments = &ColorAttachment;
		RenderPassInfo.subpassCount = 1;
		RenderPassInfo.pSubpasses = &subpass;

		VkSubpassDependency Dependency{};
		Dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		Dependency.dstSubpass = 0;
		Dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		Dependency.srcAccessMask = 0;
		Dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		Dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		RenderPassInfo.dependencyCount = 1;
		RenderPassInfo.pDependencies = &Dependency;

		if (vkCreateRenderPass(m_vulkan_rhi->m_device, &RenderPassInfo, nullptr, &m_framebuffer.render_pass) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create render pass!");
		}
	}
}
