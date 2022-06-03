#pragma once
#include "Runtime/Function/Render/RHI.h"

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

namespace ME
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_graphics_family;
		std::optional<uint32_t> m_present_family;

		bool IsComplete() const { return m_graphics_family.has_value() && m_present_family.has_value(); }
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR		m_capabilities{};
		std::vector<VkSurfaceFormatKHR> m_formats;
		std::vector<VkPresentModeKHR>	m_presentModes;
	};

	class VulkanRHI final : public RHI
	{
	public:
		// override functions
		virtual ~VulkanRHI() override final;
		virtual void Initialize(RHIInitInfo init_info) override final;
		virtual void PrepareContext() override final;

	public:
		GLFWwindow*			m_window{ nullptr };
		VkInstance			m_instance{ VK_NULL_HANDLE };
		VkPhysicalDevice	m_physical_device{ VK_NULL_HANDLE };
		QueueFamilyIndices	m_queue_indices;
		VkDevice			m_device{ VK_NULL_HANDLE };
		VkQueue				m_graphics_queue{ VK_NULL_HANDLE };
		VkQueue				m_present_queue{ VK_NULL_HANDLE };
		VkCommandPool		m_command_pool{ VK_NULL_HANDLE };

		VkSwapchainKHR				m_swapchain{ VK_NULL_HANDLE };
		VkFormat					m_swapchain_image_format{ VK_FORMAT_UNDEFINED };
		std::vector<VkImage>		m_swapchain_images;
		std::vector<VkImageView>	m_swapchain_imageviews;

		std::vector<VkFramebuffer>	m_swapchain_framebuffers;

		// global descriptor pool
		VkDescriptorPool m_descriptor_pool;

		// set
		VkCommandBuffer m_current_command_buffer;
	};
}

