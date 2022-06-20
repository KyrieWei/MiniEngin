#pragma once

#include "Runtime/Function/Render/RenderType.h"
#include "Runtime/Function/Render/RenderSwapContext.h"

#include <memory>

namespace ME
{
	class WindowSystem;
	class RHI;
	class RenderResourceBase;
	class RenderPipelineBase;
	class RenderCamera;
	class RenderScene;

	struct RenderSystemInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	class RenderSystem
	{
	public:
		RenderSystem() = default;
		~RenderSystem();

		void Initialize(RenderSystemInitInfo init_info);
		void Tick();

	private:
		RENDER_PIPELINE_TYPE m_render_pipeline_type{ RENDER_PIPELINE_TYPE::DEFERRED_PIPELINE };

		RenderSwapContext m_swap_context;

		std::shared_ptr<RHI> m_rhi;
		std::shared_ptr<RenderCamera>		m_render_camera;
		std::shared_ptr<RenderScene>		m_render_scene;
		std::shared_ptr<RenderResourceBase> m_render_resource;
		std::shared_ptr<RenderPipelineBase> m_render_pipeline;

		void ProcessSwapData();
	};

} // namespace ME
