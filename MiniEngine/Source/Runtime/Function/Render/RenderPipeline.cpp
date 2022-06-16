#include "RenderPipeline.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"

#include "Runtime/Function/Render/Passes/MainCameraPass.h"
#include "Runtime/Function/Render/Passes/UIPass.h"

namespace ME
{
	void RenderPipeline::Initialize(RenderPipelineInitInfo init_info)
	{
		m_main_camera_pass	= std::make_shared<MainCameraPass>();
		m_ui_pass			= std::make_shared<UIPass>();
		
		RenderPassCommonInfo pass_common_info;
		pass_common_info.rhi = m_rhi;
		pass_common_info.render_resource = init_info.render_resource;

		//std::shared_ptr<MainCameraPass> main_camera_pass = std::static_pointer_cast<MainCameraPass>(m_main_camera_pass);
		//std::shared_ptr<RenderPass> _main_camera_pass = std::static_pointer_cast<RenderPass>(m_main_camera_pass);

		m_main_camera_pass->SetCommonInfo(pass_common_info);
		m_ui_pass->SetCommonInfo(pass_common_info);

		m_main_camera_pass->Initialize(nullptr);

		UIPassInitInfo ui_init_info;
		//ui_init_info.render_pass 
		m_ui_pass->Initialize(&ui_init_info);
	}

	void RenderPipeline::ForwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource)
	{
		VulkanRHI* vulkan_rhi = static_cast<VulkanRHI*>(rhi.get());

		UIPass& ui_pass = *(static_cast<UIPass*>(m_ui_pass.get()));

		vulkan_rhi->WaitForFences();
		bool recreate_swapchain = vulkan_rhi->PrepareBeforePass();
		if (recreate_swapchain)
		{
			return;
		}

		static_cast<MainCameraPass*>(m_main_camera_pass.get())->DrawForward(ui_pass, vulkan_rhi->m_current_swapchain_image_index);

		vulkan_rhi->SubmitRendering();
	}

	void RenderPipeline::DeferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource)
	{
		VulkanRHI* vulkan_rhi = static_cast<VulkanRHI*>(rhi.get());

		vulkan_rhi->WaitForFences();

		vulkan_rhi->ResetCommandPool();

		bool recreate_swapchain = vulkan_rhi->PrepareBeforePass();
		if (recreate_swapchain)
		{
			return;
		}

		UIPass& ui_pass = *(static_cast<UIPass*>(m_ui_pass.get()));

		static_cast<MainCameraPass*>(m_main_camera_pass.get())
			->Draw(ui_pass, vulkan_rhi->m_current_swapchain_image_index);

		vulkan_rhi->SubmitRendering();
	}
}