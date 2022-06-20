#include "RenderSystem.h"

#include "Runtime/Core/Base/Macro.h"
#include "Runtime/Function/Render/RenderPipeline.h"
#include "Runtime/Function/Render/RenderResource.h"
#include "Runtime/Function/Render/RHI/Vulkan/VulkanRHI.h"
#include "Runtime/Function/Render/RenderCamera.h"
#include "Runtime/Function/Render/RenderScene.h"

namespace ME
{
	RenderSystem::~RenderSystem()
	{

	}

	void RenderSystem::Initialize(RenderSystemInitInfo init_info)
	{

		// render context initialize
		RHIInitInfo rhi_init_info;
		rhi_init_info.window_system = init_info.window_system;

		m_rhi = std::make_shared<VulkanRHI>();
		m_rhi->Initialize(rhi_init_info);

		// upload ibl, color grading textures
		LevelResourceDesc level_resource_desc;
		
		m_render_resource = std::make_shared<RenderResource>();
		m_render_resource->UploadGlobalRenderResource(m_rhi, level_resource_desc);

		// setup render camera
		m_render_camera = std::make_shared<RenderCamera>();

		// setup render scene
		m_render_scene = std::make_shared<RenderScene>();


		// initialize render pipeline
		RenderPipelineInitInfo pipeline_init_info;
		pipeline_init_info.render_resource = m_render_resource;

		
		

		m_render_pipeline = std::make_shared<RenderPipeline>();
		m_render_pipeline->m_rhi = m_rhi;
		m_render_pipeline->Initialize(pipeline_init_info);
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
		RenderSwapData& swap_data = m_swap_context.GetRenderSwapData();

		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
		assert(asset_manager);

		// TODO: update global resources if needed
		

		// update game object if needed
		if (swap_data.m_game_object_resource_desc.has_value())
		{
			while (!swap_data.m_game_object_resource_desc->IsEmpty())
			{
				GameObjectDesc gobject = swap_data.m_game_object_resource_desc->GetNextProcessObject();

				//for()
			}
		}

	}

} // namespace ME