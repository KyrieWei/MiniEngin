#pragma once

#include "Runtime/Function/Render/RHI.h"

#include <vector>
#include <string>

namespace ME
{
	class VulkanUtil
	{
	public:

		static uint32_t		FindMemoryType(VkPhysicalDevice			physical_device,
										   uint32_t					type_filter,
										   VkMemoryPropertyFlags	properties_flag);

		static VkShaderModule CreateShaderModule(VkDevice device, const std::vector<char>& shader_code);

		static void			CreateImage(VkPhysicalDevice		physical_device,
										VkDevice				device,
										uint32_t				image_width,
										uint32_t				image_height,
										VkFormat				format,
										VkImageTiling			image_tiling,
										VkImageUsageFlags		image_usage_flags,
										VkMemoryPropertyFlags	memory_property_flags,
										VkImage&				image,
										VkDeviceMemory&			memory,
										VkImageCreateFlags		image_create_flags,
										uint32_t				array_layers,
										uint32_t				miplevels);

		static VkImageView  CreateImageView(VkDevice			device,
											VkImage&			image,
											VkFormat&			format,
											VkImageAspectFlags	image_aspect_flags,
											VkImageViewType		view_type,
											uint32_t			layout_count,
											uint32_t			miplevels);

		static std::vector<char> ReadFile(const std::string& filename);
	};
}