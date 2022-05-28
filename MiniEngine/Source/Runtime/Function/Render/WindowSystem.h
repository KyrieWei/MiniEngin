#pragma once

//#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

#include <array>


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

		void Initialize(WindowCreateInfo create_info);
		void PollEvents() const;
		bool ShouldClose() const;
		bool SetTitle(const char* title);
		GLFWwindow* GetWindow() const;
		std::array<int, 2> GetWindowSize() const;

	private:
		GLFWwindow* m_window{ nullptr };
		int m_width{ 0 };
		int m_height{ 0 };
	};


} // namespace ME

