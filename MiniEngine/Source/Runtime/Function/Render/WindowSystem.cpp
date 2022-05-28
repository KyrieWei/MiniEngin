#include "WindowSystem.h"

namespace ME
{
	WindowSystem::~WindowSystem()
	{

	}

	void WindowSystem::Initialize(WindowCreateInfo create_info)
	{
		if (!glfwInit())
		{
			// TODO: ADD LOG
			return;
		}

		m_width = create_info.width;
		m_height = create_info.height;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(create_info.width, create_info.height, create_info.title, nullptr, nullptr);
		if (!m_window)
		{
			// TODO: ADD LOG
			glfwTerminate();
			return;
		}

		// Setup input callbacks
	}

	bool WindowSystem::ShouldClose() const { return glfwWindowShouldClose(m_window); }

	GLFWwindow* WindowSystem::GetWindow() const { return m_window; }

}