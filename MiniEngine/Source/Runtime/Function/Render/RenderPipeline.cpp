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
		
		std::shared_ptr<MainCameraPass> main_camera_pass = std::static_pointer_cast<MainCameraPass>(m_main_camera_pass);
		std::shared_ptr<RenderPass> _main_camera_pass = std::static_pointer_cast<RenderPass>(m_main_camera_pass);

		main_camera_pass->Initialize(nullptr);

		UIPassInitInfo ui_init_info;
		//ui_init_info.render_pass 
		m_ui_pass->Initialize(&ui_init_info);
	}

	void RenderPipeline::ForwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource)
	{
		VulkanRHI* vulkan_rhi = static_cast<VulkanRHI*>(rhi.get());

		UIPass& ui_pass = *(static_cast<UIPass*>(m_ui_pass.get()));

		
	}

	void RenderPipeline::DeferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResourceBase> render_resource)
	{
		VulkanRHI* vulkan_rhi = static_cast<VulkanRHI*>(rhi.get());

		
	}
}