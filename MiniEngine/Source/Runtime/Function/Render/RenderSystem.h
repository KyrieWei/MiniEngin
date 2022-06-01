#pragma once

#include "Runtime/Function/Render/RenderType.h"

#include <memory>

namespace ME
{
	class WindowSystem;
	class RHI;
	class RenderResourceBase;
	class RenderPipelineBase;

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

		std::shared_ptr<RHI> m_rhi;
		std::shared_ptr<RenderResourceBase> m_render_resource;
		std::shared_ptr<RenderPipelineBase> m_render_pipeline;

		void ProcessSwapData();
	};

} // namespace ME
