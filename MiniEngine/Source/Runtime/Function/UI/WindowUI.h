#pragma once

#include <memory>

namespace ME
{
	class WindowSystem;

	struct WindowUIInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	class WindowUI
	{
	public:
		virtual void Initialize(WindowUIInitInfo init_info) = 0;
		virtual void PreRender() = 0;
	};
}
