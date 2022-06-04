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

		// debug utilities label
		PFN_vkCmdBeginDebugUtilsLabelEXT m_vk_cmd_begin_debug_utils_label_ext;
		PFN_vkCmdEndDebugUtilsLabelEXT m_vk_cmd_end_debug_utils_label_ext;

	private:
		void CreateInstance();
		void InitializeDebugMessenger();
		void CreateWindowSurface();
		void InitializePhysicalDevice();
		void CreateLogicalDevice();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateDescriptorPool();

		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		VkResult CreateDebugUtilsMessengerEXT(VkInstance								instance,
											  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
											  const VkAllocationCallbacks*				pAllocator,
											  VkDebugUtilsMessengerEXT*					pDebugMessenger);

		void	 DestroyDebugUtilsMessengerEXT(VkInstance					instance,
											   VkDebugUtilsMessengerEXT		debugMessenger,
											   const VkAllocationCallbacks* pAllocator);
		
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physical_device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice physical_device);
		bool IsDeviceSuitable(VkPhysicalDevice physical_device);
		SwapChainSupportDetails QuerySwapchainSupport(VkPhysicalDevice physical_device);

	public:
		GLFWwindow*			m_window{ nullptr };
		VkInstance			m_instance{ VK_NULL_HANDLE };
		VkSurfaceKHR		m_surface{ VK_NULL_HANDLE };
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

		// function pointers
		

		// global descriptor pool
		VkDescriptorPool m_descriptor_pool;

		// set
		VkCommandBuffer m_current_command_buffer;
		VkViewport m_viewport;
		VkRect2D m_scissor;

	private:
		const std::vector<const char*> m_validation_layers = { "VK_LAYER_KHRONOS_validation" };
		uint32_t m_vulkan_api_version{ VK_API_VERSION_1_0 };

		std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		VkDebugUtilsMessengerEXT m_debug_messenger{ VK_NULL_HANDLE };
	};
}

