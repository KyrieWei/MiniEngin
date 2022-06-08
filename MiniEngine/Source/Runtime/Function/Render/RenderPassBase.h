#pragma once

#include "Runtime/Function/Render/RHI.h"

namespace ME
{
	class RHI;
	class RenderResourceBase;
	class WindowUI;

	struct RenderPassInitInfo
	{

	};

	struct RenderPassCommonInfo
	{
		std::shared_ptr<RHI> rhi;
		std::shared_ptr<RenderResourceBase> render_resource;
	};

	class RenderPassBase
	{
	public:
		virtual void Initialize(const RenderPassInitInfo* init_info) = 0;
		virtual void PostInitialize();
		virtual void SetCommonInfo(RenderPassCommonInfo common_info);
		virtual void PreparePassData(std::shared_ptr<RenderResourceBase> render_resource);
		virtual void InitializeUIRenderBackend(WindowUI* window_ui);

	protected:
		std::shared_ptr<RHI>				m_rhi;
		std::shared_ptr<RenderResourceBase> m_render_resource;
	};
}


