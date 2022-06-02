#pragma once

#include "Runtime/Function/Render/RenderPass.h"

namespace ME
{
	class WindowUI;

	struct UIPassInitInfo : RenderPassInitInfo
	{
		VkRenderPass render_pass;
	};

	class UIPass : public RenderPass
	{
	public:
		void Initialize(const RenderPassInitInfo* init_info) override final;
		void InitializeUIRenderBackend(WindowUI* window_ui) override final;
		void Draw() override final;
		
	private:
		WindowUI* m_window_ui;
	};
} // namespace ME
