#pragma once

#include <memory>

namespace ME
{
	class WindowSystem;

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

	};

} // namespace ME
