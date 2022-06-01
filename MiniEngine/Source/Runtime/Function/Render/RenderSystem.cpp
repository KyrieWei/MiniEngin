#include "RenderSystem.h"

#include "Runtime/Core/Base/Macro.h"
#include "Runtime/Function/Render/RenderPipeline.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"

namespace ME
{
	RenderSystem::~RenderSystem()
	{

	}

	void RenderSystem::Initialize(RenderSystemInitInfo init_info)
	{
		RHIInitInfo rhi_init_info;
		rhi_init_info.window_system = init_info.window_system;

		m_rhi = std::make_shared<VulkanRHI>();
		m_rhi->Initialize(rhi_init_info);
	}

	void RenderSystem::Tick()
	{
		// process swap data between logic and render contexts
		ProcessSwapData();

		// prepare render command context
		m_rhi->PrepareContext();

		// render one frame
		if (m_render_pipeline_type == RENDER_PIPELINE_TYPE::FORWARD_PIPELINE)
		{
			m_render_pipeline->ForwardRender(m_rhi, m_render_resource);
		}
		else if (m_render_pipeline_type == RENDER_PIPELINE_TYPE::DEFERRED_PIPELINE)
		{
			m_render_pipeline->DeferredRender(m_rhi, m_render_resource);
		}
		else
		{
			LOG_ERROR(__FUNCTION__, "unsupported render pipeline type");
		}
	}

	void RenderSystem::ProcessSwapData()
	{

	}

} // namespace ME