#include "MainCameraPass.h"

#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanUtil.h"

#include <stdexcept>

namespace ME
{
	void MainCameraPass::Initialize(const RenderPassInitInfo* init_info)
	{
		RenderPass::Initialize(nullptr);

		SetupAttachments();
		SetupRenderPass();
		SetupPipelines();
		SetupSwapchainFramebuffers();
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
		ColorAttachment.format			= m_vulkan_rhi->m_swapchain_image_format;
		ColorAttachment.samples			= VK_SAMPLE_COUNT_1_BIT;
		ColorAttachment.loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
		ColorAttachment.storeOp			= VK_ATTACHMENT_STORE_OP_STORE;
		ColorAttachment.stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		ColorAttachment.stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
		ColorAttachment.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
		ColorAttachment.finalLayout		= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

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

	void MainCameraPass::SetupPipelines()
	{
		m_render_pipelines.resize(1);

		VkPipelineLayoutCreateInfo pipeline_layout_create_info{};
		pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_create_info.setLayoutCount = 0;
		pipeline_layout_create_info.pSetLayouts = nullptr;
		pipeline_layout_create_info.pushConstantRangeCount = 0;
		pipeline_layout_create_info.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(m_vulkan_rhi->m_device, &pipeline_layout_create_info, nullptr, &m_render_pipelines[0].layout) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create pipeline layout!");
		}


		auto MESH_VERT = VulkanUtil::ReadFile("vert.spv");
		auto MESH_FRAG = VulkanUtil::ReadFile("frag.spv");
		VkShaderModule vert_shader_module = VulkanUtil::CreateShaderModule(m_vulkan_rhi->m_device, MESH_VERT);
		VkShaderModule frag_shader_module = VulkanUtil::CreateShaderModule(m_vulkan_rhi->m_device, MESH_FRAG);

		VkPipelineShaderStageCreateInfo vert_pipeline_shader_stage_create_info{};
		vert_pipeline_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vert_pipeline_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vert_pipeline_shader_stage_create_info.module = vert_shader_module;
		vert_pipeline_shader_stage_create_info.pName = "main";

		VkPipelineShaderStageCreateInfo frag_pipeline_shader_stage_create_info{};
		frag_pipeline_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		frag_pipeline_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		frag_pipeline_shader_stage_create_info.module = frag_shader_module;
		frag_pipeline_shader_stage_create_info.pName = "main";

		VkPipelineShaderStageCreateInfo shader_stages[] = { vert_pipeline_shader_stage_create_info,
															frag_pipeline_shader_stage_create_info };

		VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info{};
		vertex_input_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_state_create_info.vertexBindingDescriptionCount = 0;
		vertex_input_state_create_info.pVertexBindingDescriptions = nullptr;
		vertex_input_state_create_info.vertexAttributeDescriptionCount = 0;
		vertex_input_state_create_info.pVertexAttributeDescriptions = nullptr;

		VkPipelineInputAssemblyStateCreateInfo input_assembly_create_info;
		input_assembly_create_info.sType	= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_create_info.primitiveRestartEnable = VK_FALSE;
		input_assembly_create_info.pNext	= nullptr;
		input_assembly_create_info.flags	= 0;

		VkPipelineViewportStateCreateInfo viewport_state_create_info{};
		viewport_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state_create_info.viewportCount = 1;
		viewport_state_create_info.pViewports = &m_vulkan_rhi->m_viewport;
		viewport_state_create_info.scissorCount = 1;
		viewport_state_create_info.pScissors = &m_vulkan_rhi->m_scissor;

		VkPipelineRasterizationStateCreateInfo rasterization_state_create_info{};
		rasterization_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterization_state_create_info.depthClampEnable = VK_FALSE;
		rasterization_state_create_info.rasterizerDiscardEnable = VK_FALSE;
		rasterization_state_create_info.polygonMode = VK_POLYGON_MODE_FILL;
		rasterization_state_create_info.lineWidth = 1.0f;
		rasterization_state_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterization_state_create_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterization_state_create_info.depthBiasEnable = VK_FALSE;
		rasterization_state_create_info.depthBiasConstantFactor = 0.0f;
		rasterization_state_create_info.depthBiasClamp = 0.0f;
		rasterization_state_create_info.depthBiasSlopeFactor = 0.0f;

		VkPipelineMultisampleStateCreateInfo multisample_state_create_info{};
		multisample_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisample_state_create_info.sampleShadingEnable = VK_FALSE;
		multisample_state_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState color_blend_attachments{};
		color_blend_attachments.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
												 VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		color_blend_attachments.blendEnable			= VK_FALSE;
		color_blend_attachments.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachments.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachments.colorBlendOp		= VK_BLEND_OP_ADD;
		color_blend_attachments.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachments.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachments.alphaBlendOp		= VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo color_blend_state_create_info{};
		color_blend_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blend_state_create_info.logicOpEnable = VK_FALSE;
		color_blend_state_create_info.logicOp = VK_LOGIC_OP_COPY;
		color_blend_state_create_info.attachmentCount = 1;
		color_blend_state_create_info.pAttachments = &color_blend_attachments;
		color_blend_state_create_info.blendConstants[0] = 0.0f;
		color_blend_state_create_info.blendConstants[1] = 0.0f;
		color_blend_state_create_info.blendConstants[2] = 0.0f;
		color_blend_state_create_info.blendConstants[3] = 0.0f;

		VkDynamicState dynamic_states[] =
		{
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamic_state_create_info{};
		dynamic_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state_create_info.dynamicStateCount = 2;
		dynamic_state_create_info.pDynamicStates = dynamic_states;

		VkGraphicsPipelineCreateInfo pipeline_create_info{};
		pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_create_info.stageCount = 2;
		pipeline_create_info.pStages = shader_stages;
		pipeline_create_info.pVertexInputState = &vertex_input_state_create_info;
		pipeline_create_info.pInputAssemblyState = &input_assembly_create_info;
		pipeline_create_info.pViewportState = &viewport_state_create_info;
		pipeline_create_info.pRasterizationState = &rasterization_state_create_info;
		pipeline_create_info.pMultisampleState = &multisample_state_create_info;
		pipeline_create_info.pColorBlendState = &color_blend_state_create_info;
		pipeline_create_info.pDepthStencilState = nullptr;
		pipeline_create_info.layout = m_render_pipelines[0].layout;
		pipeline_create_info.renderPass = m_framebuffer.render_pass;
		pipeline_create_info.subpass = 0;
		pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
		pipeline_create_info.basePipelineIndex = -1;
		pipeline_create_info.pDynamicState = nullptr;

		if (vkCreateGraphicsPipelines(	m_vulkan_rhi->m_device,
										VK_NULL_HANDLE,
										1,
										&pipeline_create_info,
										nullptr,
										&m_render_pipelines[0].pipeline) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create graphics pipeline");
		}

		vkDestroyShaderModule(m_vulkan_rhi->m_device, vert_shader_module, nullptr);
		vkDestroyShaderModule(m_vulkan_rhi->m_device, frag_shader_module, nullptr);
	}

	void MainCameraPass::SetupSwapchainFramebuffers()
	{
		m_swapchain_framebuffers.resize(m_vulkan_rhi->m_swapchain_imageviews.size());

		// create frame buffer for every imageview
		for (size_t i = 0; i < m_vulkan_rhi->m_swapchain_imageviews.size(); i++)
		{
			VkImageView framebuffer_attachments_for_image_view[] = { m_vulkan_rhi->m_swapchain_imageviews[i] };

			VkFramebufferCreateInfo framebuffer_create_info{};
			framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebuffer_create_info.renderPass = m_framebuffer.render_pass;
			framebuffer_create_info.attachmentCount = 1;
			framebuffer_create_info.pAttachments = framebuffer_attachments_for_image_view;
			framebuffer_create_info.width = m_vulkan_rhi->m_swapchain_extent.width;
			framebuffer_create_info.height = m_vulkan_rhi->m_swapchain_extent.height;
			framebuffer_create_info.layers = 1;

			if (vkCreateFramebuffer(m_vulkan_rhi->m_device, &framebuffer_create_info, nullptr, &m_swapchain_framebuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create framebuffer!");
			}
		}
	} 

	void MainCameraPass::Draw(	UIPass& ui_pass,
								uint32_t current_swapchain_image_index)
	{
		{
			VkRenderPassBeginInfo renderpass_begin_info{};
			renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderpass_begin_info.renderPass = m_framebuffer.render_pass;
			renderpass_begin_info.framebuffer = m_swapchain_framebuffers[current_swapchain_image_index];
			renderpass_begin_info.renderArea.offset = { 0, 0 };
			renderpass_begin_info.renderArea.extent = m_vulkan_rhi->m_swapchain_extent;

			VkClearValue clear_values = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderpass_begin_info.clearValueCount = 1;
			renderpass_begin_info.pClearValues = &clear_values;

			m_vulkan_rhi->m_vk_cmd_begin_render_pass(m_vulkan_rhi->m_current_command_buffer, &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

			m_vulkan_rhi->m_vk_cmd_bind_pipeline(m_vulkan_rhi->m_current_command_buffer,
													VK_PIPELINE_BIND_POINT_GRAPHICS,
													m_render_pipelines[0].pipeline);

			vkCmdDraw(m_vulkan_rhi->m_current_command_buffer, 3, 1, 0, 0);

			m_vulkan_rhi->m_vk_cmd_end_render_pass(m_vulkan_rhi->m_current_command_buffer);

			if (m_vulkan_rhi->m_vk_end_command_buffer(m_vulkan_rhi->m_current_command_buffer) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to record command buffer!");
			}
		}
	}

	void MainCameraPass::DrawForward(UIPass& ui_pass,
									 uint32_t current_swapchain_image_index)
	{

	}
}
