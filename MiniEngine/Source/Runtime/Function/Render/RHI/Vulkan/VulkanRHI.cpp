#include "VulkanRHI.h"
#include "VulkanUtil.h"
#include "Runtime/Function/Render/WindowSystem.h"

#define VMA_IMPLEMENTATION 1
#include <vulkanmemallocator/vk_mem_alloc.h>

#include <algorithm>
#include <cassert>

#include <iostream>
#include <stdexcept>
#include <set>

namespace ME
{
	VulkanRHI::~VulkanRHI()
	{
		// TODO
	}

	void VulkanRHI::Initialize(RHIInitInfo init_info)
	{
		m_window = init_info.window_system->GetWindow();

		std::array<int, 2> window_size = init_info.window_system->GetWindowSize();

		m_viewport = { 0.0f, 0.0f, (float)window_size[0], (float)window_size[1], 0.0f, 1.0f };
		m_scissor = { {0, 0}, {(uint32_t)window_size[0], (uint32_t)window_size[1]} };

#ifndef NDEBUG
		m_enable_validation_layers = true;
		m_enable_debug_utils_label = true;
#else
		m_enable_validation_layers = false;
		m_enable_debug_utils_label = false;
#endif // !NDEBUG


		CreateInstance();

		//InitializeDebugMessenger();

		CreateWindowSurface();

		InitializePhysicalDevice();

		CreateLogicalDevice();



		//CreateDescriptorPool();


		CreateSwapchain();

		CreateSwapchainImageViews();

		//CreateFramebufferImageAndView();

		//CreateAssetAllocator();

		CreateCommandPool();

		CreateCommandBuffers();

		CreateSyncPrimitives();
	}

	void VulkanRHI::PrepareContext()
	{
		m_p_current_frame_index		= &m_current_frame_index;
		m_current_command_buffer	= m_command_buffers[m_current_frame_index];
		m_p_command_buffers			= m_command_buffers;
		m_p_command_pools			= m_command_pools;
	}

	void VulkanRHI::Clear()
	{
		
	}

	void VulkanRHI::WaitForFences()
	{
		VkResult res_wait_for_fences =
			m_vk_wait_for_fences(m_device, 1, &m_is_frame_in_flight_fences[m_current_frame_index], VK_TRUE, UINT64_MAX);
		if (res_wait_for_fences != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to synchronize!");
		}
	}

	void VulkanRHI::ResetCommandPool()
	{
		VkResult res_reset_command_pool = m_vk_reset_command_pool(m_device, m_command_pools[m_current_frame_index], 0);
		if (VK_SUCCESS != res_reset_command_pool)
		{
			throw std::runtime_error("Failed to synchronize!");
		}
	}

	bool VulkanRHI::PrepareBeforePass()
	{
		VkResult acquire_image_result = 
			vkAcquireNextImageKHR(m_device,
									m_swapchain,
									UINT64_MAX,
									m_image_available_for_render_semaphores[m_current_frame_index],
									VK_NULL_HANDLE,
									&m_current_swapchain_image_index);

		if (VK_ERROR_OUT_OF_DATE_KHR == acquire_image_result)
		{
			//RecreateSwapchain();
			return true;
		}
		//else if (VK_SUBOPTIMAL_KHR == acquire_image_result)
		//{
		//	//RecreateSwapchain();

		//	// NULL submit to wait semaphore
		//	VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT };
		//	VkSubmitInfo submit_info = {};
		//	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		//	submit_info.waitSemaphoreCount = 1;
		//	submit_info.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];
		//	submit_info.pWaitDstStageMask = wait_stages;
		//	submit_info.commandBufferCount = 0;
		//	submit_info.pCommandBuffers = NULL;
		//	submit_info.signalSemaphoreCount = 0;
		//	submit_info.pSignalSemaphores = NULL;

		//	VkResult res_reset_fences = m_vk_reset_fences(m_device, 1, &m_is_frame_in_flight_fences[m_current_frame_index]);
		//	assert(VK_SUCCESS == res_reset_fences);

		//	VkResult res_queue_submit =
		//		vkQueueSubmit(m_graphics_queue, 1, &submit_info, m_is_frame_in_flight_fences[m_current_frame_index]);
		//	assert(VK_SUCCESS == res_queue_submit);

		//	m_current_frame_index = (m_current_frame_index + 1) % m_max_frames_in_flight;
		//	
		//	return true;
		//}
		else
		{
			assert(VK_SUCCESS == acquire_image_result);
		}

		

		// begin command buffer
		VkCommandBufferBeginInfo command_buffer_begin_info{};
		command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		command_buffer_begin_info.flags = 0;
		command_buffer_begin_info.pInheritanceInfo = nullptr;

		VkResult res_begin_command_buffer =
			m_vk_begin_command_buffer(m_command_buffers[m_current_frame_index], &command_buffer_begin_info);
		assert(VK_SUCCESS == res_begin_command_buffer);

		return false;
	}

	void VulkanRHI::SubmitRendering()
	{
		// end command buffer
		VkResult res_end_command_buffer = m_vk_end_command_buffer(m_command_buffers[m_current_frame_index]);
		assert(VK_SUCCESS == res_end_command_buffer);

		// submit command buffer
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_command_buffers[m_current_swapchain_image_index];
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &m_image_finished_for_presentation_semaphores[m_current_frame_index];

		VkResult res_reset_fences = m_vk_reset_fences(m_device, 1, &m_is_frame_in_flight_fences[m_current_frame_index]);
		assert(VK_SUCCESS == res_reset_fences);

		if (vkQueueSubmit(m_graphics_queue, 1, &submitInfo, m_is_frame_in_flight_fences[m_current_frame_index]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to submit draw command buffer!");
		}

		VkPresentInfoKHR present_info{};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = &m_image_finished_for_presentation_semaphores[m_current_frame_index];
		present_info.swapchainCount = 1;
		present_info.pSwapchains = &m_swapchain;
		present_info.pImageIndices = &m_current_swapchain_image_index;

		VkResult present_result = vkQueuePresentKHR(m_present_queue, &present_info);
		if (VK_ERROR_OUT_OF_DATE_KHR == present_result || VK_SUBOPTIMAL_KHR == present_result)
		{

		}
		else
		{
			assert(VK_SUCCESS == present_result);
		}
		//vkQueueWaitIdle(m_present_queue);

		m_current_frame_index = (m_current_frame_index + 1) % m_max_frames_in_flight;
	}

	bool VulkanRHI::CheckValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_validation_layers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	std::vector<const char*> VulkanRHI::GetRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (m_enable_validation_layers || m_enable_debug_utils_label)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	// debug callback
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT,
		VkDebugUtilsMessageTypeFlagsEXT,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void*)
	{
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	void VulkanRHI::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = DebugCallback;
	}

	void VulkanRHI::CreateInstance()
	{
		// validation layer will be enabled in debug mode
		if (m_enable_validation_layers && !CheckValidationLayerSupport())
		{
			throw std::runtime_error("validation layers requested, but not available!");
		}

		m_vulkan_api_version = VK_API_VERSION_1_0;

		// app info
		VkApplicationInfo appInfo{};
		appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName	= "MiniEngine_Renderer";
		appInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName			= "MiniEngine";
		appInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion			= m_vulkan_api_version;

		// create info
		VkInstanceCreateInfo instance_create_info{};
		instance_create_info.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_create_info.pApplicationInfo	= &appInfo;

		auto extensions								 = GetRequiredExtensions();
		instance_create_info.enabledExtensionCount	 = static_cast<uint32_t>(extensions.size());
		instance_create_info.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (m_enable_validation_layers)
		{
			instance_create_info.enabledLayerCount		= static_cast<uint32_t>(m_validation_layers.size());
			instance_create_info.ppEnabledLayerNames	= m_validation_layers.data();

			//PopulateDebugMessengerCreateInfo(debugCreateInfo);
			//instance_create_info.pNext					= (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			instance_create_info.enabledLayerCount	= 0;
			instance_create_info.pNext				= nullptr;
		}

		// create m_vulkan_context._instance
		if (vkCreateInstance(&instance_create_info, nullptr, &m_instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create instance");
		}

	}

	void VulkanRHI::InitializeDebugMessenger()
	{
		if (m_enable_validation_layers)
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			PopulateDebugMessengerCreateInfo(createInfo);
			if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debug_messenger) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to set up debug messenger!");
			}
		}

		if (m_enable_debug_utils_label)
		{
			m_vk_cmd_begin_debug_utils_label_ext =
				(PFN_vkCmdBeginDebugUtilsLabelEXT)vkGetInstanceProcAddr(m_instance, "vkCmdBeginDebugUtilsLabelEXT");
			m_vk_cmd_end_debug_utils_label_ext =
				(PFN_vkCmdEndDebugUtilsLabelEXT)vkGetInstanceProcAddr(m_instance, "vkCmdEndDebugUtilsLabelEXT");
		}
	}

	void VulkanRHI::CreateWindowSurface()
	{
		if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create window surface!");
		}
	}

	void VulkanRHI::InitializePhysicalDevice()
	{
		uint32_t physical_device_count;
		vkEnumeratePhysicalDevices(m_instance, &physical_device_count, nullptr);
		if (physical_device_count == 0)
		{
			throw std::runtime_error("Failed to find GUPs with vulkan support!");
		}
		else
		{
			// find one device that matches our requirement
			// or find which is the best
			std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
			vkEnumeratePhysicalDevices(m_instance, &physical_device_count, physical_devices.data());

			std::vector<std::pair<int, VkPhysicalDevice>> ranked_physical_devices;
			for (const auto& device : physical_devices)
			{
				VkPhysicalDeviceProperties physical_device_properties;
				vkGetPhysicalDeviceProperties(device, &physical_device_properties);
				int score = 0;

				if (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				{
					score += 1000;
				}
				else if (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				{
					score += 100;
				}

				ranked_physical_devices.push_back({ score, device });
			}

			std::sort(ranked_physical_devices.begin(),
				ranked_physical_devices.end(),
				[](const std::pair<int, VkPhysicalDevice>& p1, const std::pair<int, VkPhysicalDevice>& p2)
				{
					return p1 > p2;
				});

			for (const auto& device : ranked_physical_devices)
			{
				if (IsDeviceSuitable(device.second))
				{
					m_physical_device = device.second;
					break;
				}
			}

			if (m_physical_device == VK_NULL_HANDLE)
			{
				throw std::runtime_error("Failed to find suitable physical device");
			}
		}
	}

	// logical device
	void VulkanRHI::CreateLogicalDevice()
	{
		m_queue_indices = FindQueueFamilies(m_physical_device);

		std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
		std::set<uint32_t> queue_families = { m_queue_indices.m_graphics_family.value(), m_queue_indices.m_present_family.value() };

		float queue_priority = 1.0f;
		for (uint32_t queue_family : queue_families) // for every queue family
		{
			// queue create info
			VkDeviceQueueCreateInfo queue_create_info{};
			queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue_create_info.queueFamilyIndex = queue_family;
			queue_create_info.queueCount = 1;
			queue_create_info.pQueuePriorities = &queue_priority;
			queue_create_infos.push_back(queue_create_info);
		}

		// physical device features
		VkPhysicalDeviceFeatures physical_device_features = {};
		//physical_device_features.samplerAnisotropy = VK_TRUE;

		// support inefficient readback storage buffer
		//physical_device_features.fragmentStoresAndAtomics = VK_TRUE;

		// support independent blending
		//physical_device_features.independentBlend = VK_TRUE;

		// support geometry shader
		//physical_device_features.geometryShader = VK_TRUE;

		// device create info
		VkDeviceCreateInfo device_create_info{};
		device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_info.pQueueCreateInfos = queue_create_infos.data();
		device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
		device_create_info.pEnabledFeatures = &physical_device_features;

		device_create_info.enabledExtensionCount = static_cast<uint32_t>(m_device_extensions.size());
		device_create_info.ppEnabledExtensionNames = m_device_extensions.data();
		//device_create_info.enabledLayerCount = 0;

		//if (m_enable_validation_layers)
		//{
		//	device_create_info.enabledLayerCount = static_cast<uint32_t>(m_validation_layers.size());
		//	device_create_info.ppEnabledLayerNames = m_validation_layers.data();
		//}
		//else
		//{
		//	device_create_info.enabledLayerCount = 0;
		//}

		if (vkCreateDevice(m_physical_device, &device_create_info, nullptr, &m_device) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create logical device!");
		}

		// initialize queues of this device
		vkGetDeviceQueue(m_device, m_queue_indices.m_graphics_family.value(), 0, &m_graphics_queue);
		vkGetDeviceQueue(m_device, m_queue_indices.m_present_family.value(), 0, &m_present_queue);

		// more efficient pointer
		m_vk_wait_for_fences = (PFN_vkWaitForFences)vkGetDeviceProcAddr(m_device, "vkWaitForFences");
		m_vk_reset_fences = (PFN_vkResetFences)vkGetDeviceProcAddr(m_device, "vkResetFences");
		m_vk_reset_command_pool = (PFN_vkResetCommandPool)vkGetDeviceProcAddr(m_device, "vkResetCommandPool");
		m_vk_begin_command_buffer = (PFN_vkBeginCommandBuffer)vkGetDeviceProcAddr(m_device, "vkBeginCommandBuffer");
		m_vk_end_command_buffer = (PFN_vkEndCommandBuffer)vkGetDeviceProcAddr(m_device, "vkEndCommandBuffer");
		m_vk_cmd_begin_render_pass = (PFN_vkCmdBeginRenderPass)vkGetDeviceProcAddr(m_device, "vkCmdBeginRenderPass");
		m_vk_cmd_end_render_pass = (PFN_vkCmdEndRenderPass)vkGetDeviceProcAddr(m_device, "vkCmdEndRenderPass");
		m_vk_cmd_bind_pipeline = (PFN_vkCmdBindPipeline)vkGetDeviceProcAddr(m_device, "vkCmdBindPipeline");
		m_vk_cmd_draw = (PFN_vkCmdDraw)vkGetDeviceProcAddr(m_device, "vkCmdDraw");

		m_depth_image_format = FindDepthFormat();
	}

	void VulkanRHI::CreateCommandPool()
	{
		// default graphics command pool
		{
			VkCommandPoolCreateInfo command_pool_create_info{};
			command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			command_pool_create_info.pNext = NULL;
			command_pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			command_pool_create_info.queueFamilyIndex = m_queue_indices.m_graphics_family.value();

			if (vkCreateCommandPool(m_device, &command_pool_create_info, nullptr, &m_command_pool) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create command pool");
			}
		}

		// other command pool
		{
			VkCommandPoolCreateInfo command_pool_create_info;
			command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			command_pool_create_info.pNext = NULL;
			command_pool_create_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
			command_pool_create_info.queueFamilyIndex = m_queue_indices.m_graphics_family.value();

			for (uint32_t i = 0; i < m_max_frames_in_flight; i++)
			{
				if (vkCreateCommandPool(m_device, &command_pool_create_info, NULL, &m_command_pools[i]) != VK_SUCCESS)
				{
					throw std::runtime_error("Failed to create command pool");
				}
			}
		}
	}

	void VulkanRHI::CreateCommandBuffers()
	{
		VkCommandBufferAllocateInfo command_buffer_allocate_info{};
		command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_allocate_info.commandBufferCount = 1U;

		for (uint32_t i = 0; i < m_max_frames_in_flight; i++)
		{
			command_buffer_allocate_info.commandPool = m_command_pools[i];
			
			if (vkAllocateCommandBuffers(m_device, &command_buffer_allocate_info, &m_command_buffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create command buffers!");
			}
		}
	}

	void VulkanRHI::CreateDescriptorPool()
	{
		VkDescriptorPoolSize pool_sizes[5];
		pool_sizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
		pool_sizes[0].descriptorCount = 3 + 2 + 2 + 2 + 1 + 1 + 3 + 3;
		pool_sizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		pool_sizes[1].descriptorCount = 1 + 1 + 1 * m_max_vertex_blending_mesh_count;
		pool_sizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_sizes[2].descriptorCount = 1 * m_max_material_count;
		pool_sizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		pool_sizes[3].descriptorCount = 3 + 5 * m_max_material_count + 1 + 1; // ImGui_ImplVulkan_CreateDeviceObjects
		pool_sizes[4].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
		pool_sizes[4].descriptorCount = 4 + 1 + 1 + 2;

		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);
		pool_info.pPoolSizes = pool_sizes;
		pool_info.maxSets = 1 + 1 + 1 + m_max_material_count + m_max_vertex_blending_mesh_count + 1 + 1;
		pool_info.flags = 0U;

		if (vkCreateDescriptorPool(m_device, &pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create descriptor pool!");
		}
	}

	void VulkanRHI::CreateSyncPrimitives()
	{
		VkSemaphoreCreateInfo semaphore_create_info{};
		semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fence_create_info{};
		fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (uint32_t i = 0; i < m_max_frames_in_flight; i++)
		{
			if (vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_available_for_render_semaphores[i])
				!= VK_SUCCESS ||
				vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_finished_for_presentation_semaphores[i])
				!= VK_SUCCESS ||
				vkCreateFence(m_device, &fence_create_info, nullptr, &m_is_frame_in_flight_fences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create semaphore & fence!");
			}
		}
	}

	void VulkanRHI::CreateSwapchainImageViews()
	{
		m_swapchain_imageviews.resize(m_swapchain_images.size());

		// create imageview (one for each this time) for all swapchain images
		for (size_t i = 0; i < m_swapchain_images.size(); i++)
		{
			m_swapchain_imageviews[i] = VulkanUtil::CreateImageView(m_device,
																	m_swapchain_images[i],
																	m_swapchain_image_format,
																	VK_IMAGE_ASPECT_COLOR_BIT,
																	VK_IMAGE_VIEW_TYPE_2D,
																	1,
																	1);
		}
	}

	void VulkanRHI::CreateFramebufferImageAndView()
	{
		VulkanUtil::CreateImage(m_physical_device,
			m_device,
			m_swapchain_extent.width,
			m_swapchain_extent.height,
			m_depth_image_format,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
			VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_depth_image,
			m_depth_image_memory,
			0,
			1,
			1);


	}

	void VulkanRHI::CreateAssetAllocator()
	{
		VmaVulkanFunctions vulkanFunctions = {};
		vulkanFunctions.vkGetInstanceProcAddr = &vkGetInstanceProcAddr;
		vulkanFunctions.vkGetDeviceProcAddr = &vkGetDeviceProcAddr;

		VmaAllocatorCreateInfo allocatorCreateInfo = {};
		allocatorCreateInfo.vulkanApiVersion = m_vulkan_api_version;
		allocatorCreateInfo.physicalDevice = m_physical_device;
		allocatorCreateInfo.device = m_device;
		allocatorCreateInfo.instance = m_instance;
		allocatorCreateInfo.pVulkanFunctions = &vulkanFunctions;

		vmaCreateAllocator(&allocatorCreateInfo, &m_assets_allocator);
	}

	void VulkanRHI::CreateSwapchain()
	{
		// query all supports of this physical device
		SwapChainSupportDetails swapchain_support_details = QuerySwapchainSupport(m_physical_device);

		// choose the best or fitting format
		VkSurfaceFormatKHR chosen_surface_format = ChooseSwapchainSurfaceFormatFromDetails(swapchain_support_details.m_formats);
		
		// choose the best or fitting present mode
		VkPresentModeKHR chosen_present_mode = ChooseSwapchainPresentModeFromDetails(swapchain_support_details.m_presentModes);

		// choose the best or fitting extent
		VkExtent2D chosen_extent = ChooseSwapchainExtentFromDetails(swapchain_support_details.m_capabilities);

		uint32_t image_count = swapchain_support_details.m_capabilities.minImageCount + 1;
		if (swapchain_support_details.m_capabilities.maxImageCount > 0 &&
			image_count > swapchain_support_details.m_capabilities.maxImageCount)
		{
			image_count = swapchain_support_details.m_capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;

		createInfo.minImageCount = image_count;
		createInfo.imageFormat = chosen_surface_format.format;
		createInfo.imageColorSpace = chosen_surface_format.colorSpace;
		createInfo.imageExtent = chosen_extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		uint32_t queueFamilyIndices[] = { m_queue_indices.m_graphics_family.value(), m_queue_indices.m_present_family.value() };

		if (m_queue_indices.m_graphics_family != m_queue_indices.m_present_family)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapchain_support_details.m_capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = chosen_present_mode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create swapchain khr!");
		}

		vkGetSwapchainImagesKHR(m_device, m_swapchain, &image_count, nullptr);
		m_swapchain_images.resize(image_count);
		vkGetSwapchainImagesKHR(m_device, m_swapchain, &image_count, m_swapchain_images.data());

		m_swapchain_image_format = chosen_surface_format.format;
		m_swapchain_extent = chosen_extent;

		m_scissor = { {0, 0}, {m_swapchain_extent.width, m_swapchain_extent.height} };
	}

	void VulkanRHI::ClearSwapchain()
	{
		for (auto imageview : m_swapchain_imageviews)
		{
			vkDestroyImageView(m_device, imageview, NULL);
		}

		vkDestroySwapchainKHR(m_device, m_swapchain, NULL);
	}

	void VulkanRHI::RecreateSwapchain()
	{
		int width = 0;
		int height = 0;
		glfwGetFramebufferSize(m_window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(m_window, &width, &height);
			glfwWaitEvents();
		}

		VkResult res_wait_for_fences = m_vk_wait_for_fences(m_device, m_max_frames_in_flight, m_is_frame_in_flight_fences, VK_TRUE, UINT64_MAX);
		assert(VK_SUCCESS == res_wait_for_fences);

		//vkDestroyImageView(m_device, m_depth)

		for (auto imageview : m_swapchain_imageviews)
		{
			vkDestroyImageView(m_device, imageview, NULL);
		}

		vkDestroySwapchainKHR(m_device, m_swapchain, NULL);

		CreateSwapchain();
		CreateSwapchainImageViews();
		CreateFramebufferImageAndView();
	}

	VkResult VulkanRHI::CreateDebugUtilsMessengerEXT(VkInstance instance,
													const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
													const VkAllocationCallbacks* pAllocator,
													VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanRHI::DestroyDebugUtilsMessengerEXT(VkInstance instance,
												  VkDebugUtilsMessengerEXT debugMessenger,
												  const VkAllocationCallbacks* pAllocator)
	{
		auto func =
			(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			func(instance, debugMessenger, pAllocator);
		}
	}

	ME::QueueFamilyIndices VulkanRHI::FindQueueFamilies(VkPhysicalDevice physical_device)
	{
		QueueFamilyIndices indices;
		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

		int i = 0;
		for (const auto& queue_family : queue_families)
		{
			if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) // if support graphics command queue
			{
				indices.m_graphics_family = i;
			}

			VkBool32 is_present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, m_surface, &is_present_support);

			if (is_present_support)
			{
				indices.m_present_family = i;
			}

			if (indices.IsComplete())
			{
				break;
			}
			i++;
		}

		return indices;
	}

	bool VulkanRHI::CheckDeviceExtensionSupport(VkPhysicalDevice physical_device)
	{
		uint32_t extension_count;
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> available_extensions(extension_count);
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, available_extensions.data());

		std::set<std::string> required_extensions(m_device_extensions.begin(), m_device_extensions.end());
		for (const auto& extension : available_extensions)
		{
			required_extensions.erase(extension.extensionName);
		}

		return required_extensions.empty();
	}

	bool VulkanRHI::IsDeviceSuitable(VkPhysicalDevice physical_device)
	{
		auto queue_indices = FindQueueFamilies(physical_device);
		bool is_extensions_supported = CheckDeviceExtensionSupport(physical_device);
		bool is_swapchain_adequate = false;
		if (is_extensions_supported)
		{
			SwapChainSupportDetails swapchain_support_details = QuerySwapchainSupport(physical_device);
			is_swapchain_adequate = !swapchain_support_details.m_formats.empty() && !swapchain_support_details.m_presentModes.empty();
		}

		//VkPhysicalDeviceFeatures physical_device_features;
		//vkGetPhysicalDeviceFeatures(physical_device, &physical_device_features);

		//if (!queue_indices.IsComplete() || !is_swapchain_adequate || !physical_device_features.samplerAnisotropy)
		//{
		//	return false;
		//}

		//return true;

		return queue_indices.IsComplete() && is_extensions_supported && is_swapchain_adequate;
	}

	ME::SwapChainSupportDetails VulkanRHI::QuerySwapchainSupport(VkPhysicalDevice physical_device)
	{
		SwapChainSupportDetails details_result;

		// capabilities
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, m_surface, &details_result.m_capabilities);

		// formats
		uint32_t format_count;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, m_surface, &format_count, nullptr);
		if (format_count != 0)
		{
			details_result.m_formats.resize(format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, m_surface, &format_count, details_result.m_formats.data());
		}

		// present mode
		uint32_t presentmode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, m_surface, &presentmode_count, nullptr);
		if (presentmode_count != 0)
		{
			details_result.m_presentModes.resize(presentmode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, m_surface, &presentmode_count, details_result.m_presentModes.data());
		}

		return details_result;
		
	}

	VkFormat VulkanRHI::FindDepthFormat()
	{
		return FindSupportedFormat({ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
									VK_IMAGE_TILING_OPTIMAL,
									VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	VkFormat VulkanRHI::FindSupportedFormat(const std::vector<VkFormat>& candiates,
											VkImageTiling					tiling,
											VkFormatFeatureFlags			features)
	{
		for (VkFormat format : candiates)
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(m_physical_device, format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
			{
				return format;
			}
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			{
				return format;
			}
		}

		throw std::runtime_error("Failed to find supported format!");
	}

	VkSurfaceFormatKHR VulkanRHI::ChooseSwapchainSurfaceFormatFromDetails(const std::vector<VkSurfaceFormatKHR>& available_surface_fromats)
	{
		for (const auto& surface_format : available_surface_fromats)
		{
			// TODO: select the VK_FORMAT_B8G8R8A8_SRGB surface format
			// there is no need to do gamma correction in the fragment shader
			if (surface_format.format == VK_FORMAT_B8G8R8A8_SRGB &&
				surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return surface_format;
			}
		}

		return available_surface_fromats[0];
	}

	VkPresentModeKHR VulkanRHI::ChooseSwapchainPresentModeFromDetails(const std::vector<VkPresentModeKHR>& available_present_modes)
	{
		for (VkPresentModeKHR present_mode : available_present_modes)
		{
			if (VK_PRESENT_MODE_MAILBOX_KHR == present_mode)
			{
				return VK_PRESENT_MODE_MAILBOX_KHR;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanRHI::ChooseSwapchainExtentFromDetails(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(m_window, &width, &height);

			VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
} // namespace ME