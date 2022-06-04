#pragma once

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

#include <memory>

namespace ME
{
	class WindowSystem;

	struct RHIInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	class RHI
	{
	public:
		virtual ~RHI() = 0;
		virtual void Initialize(RHIInitInfo init_info) = 0;
		virtual void PrepareContext() = 0;

	public:
		
	protected:
		bool m_enable_validation_layers{ true };
		bool m_enable_debug_utils_label{ true };
		//bool m_enable_point_light

	private:

	};

	inline RHI::~RHI() = default;
}

