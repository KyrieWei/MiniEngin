#include "UIPass.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"
#include "Runtime/Function/UI/WindowUI.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_vulkan.h>

namespace ME
{
	void UIPass::Initialize(const RenderPassInitInfo* init_info)
	{
		RenderPass::Initialize(nullptr);

		m_framebuffer.render_pass = static_cast<const UIPassInitInfo*>(init_info)->render_pass;
	}

	void UIPass::InitializeUIRenderBackend(WindowUI* window_ui)
	{
		m_window_ui = window_ui;

		ImGui_ImplGlfw_InitForVulkan(m_vulkan_rhi->m_window, true);
		ImGui_ImplVulkan_InitInfo init_info = {};

		init_info.Instance				= m_vulkan_rhi->m_instance;
		init_info.PhysicalDevice		= m_vulkan_rhi->m_physical_device;
		init_info.Device				= m_vulkan_rhi->m_device;
		init_info.QueueFamily			= m_vulkan_rhi->m_queue_indices.m_graphics_family.value();
		init_info.Queue					= m_vulkan_rhi->m_graphics_queue;
		init_info.DescriptorPool		= m_vulkan_rhi->m_descriptor_pool;
		init_info.Subpass				= _main_camera_subpass_ui;

		init_info.MinImageCount = 3;
		init_info.ImageCount = 3;
		ImGui_ImplVulkan_Init(&init_info, m_framebuffer.render_pass);
	}

	void UIPass::Draw()
	{
		if (m_window_ui)
		{
			ImGui_ImplVulkan_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_window_ui->PreRender();

			//if(m_vulkan_rhi->)

			ImGui::Render();

			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_vulkan_rhi->m_current_command_buffer);
		}
	}


} // namespace ME
