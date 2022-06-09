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

		VkPipelineVertexInputStateCreateInfo vertex_input_info{};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexBindingDescriptionCount = 0;
		vertex_input_info.pVertexBindingDescriptions = nullptr;
		vertex_input_info.vertexAttributeDescriptionCount = 0;
		vertex_input_info.pVertexAttributeDescriptions = nullptr;

		VkPipelineInputAssemblyStateCreateInfo input_assembly;
		input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly.primitiveRestartEnable = VK_FALSE;

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
		color_blend_attachments.blendEnable = VK_FALSE;


	}
}
