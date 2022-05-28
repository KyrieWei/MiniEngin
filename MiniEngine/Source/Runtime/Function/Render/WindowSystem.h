#pragma once

namespace ME
{
	struct WindowCreateInfo
	{
		int width{ 1280 };
		int height{ 720 };
		const char* title{ "MiniEngine" };
		bool is_full_screen{ false };
	};

	class WindowSystem
	{
	public:
		WindowSystem() = default;
		~WindowSystem();


	};


} // namespace ME

