/*
\brief Header including the smallest amount of structs to enablebasic Vulkan Safety Critical compilation
\file vulkan_sc_core_minimal.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#ifndef VULKAN_SC_CORE_MINIMAL_H_PP
#define VULKAN_SC_CORE_MINIMAL_H_PP 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VkPipelinePoolSize
{
	VkStructureType sType;
	void const* pNext;
	VkDeviceSize poolEntrySize;
	uint32_t poolEntryCount;
} VkPipelinePoolSize;

typedef struct VkDeviceObjectReservationCreateInfo
{
	VkStructureType sType;
	void const* pNext;
	uint32_t pipelineCacheCreateInfoCount;
	VkPipelineCacheCreateInfo const* pPipelineCacheCreateInfos;
	uint32_t pipelinePoolSizeCount;
	VkPipelinePoolSize const* pPipelinePoolSizes;
	uint32_t semaphoreRequestCount;
	uint32_t commandBufferRequestCount;
	uint32_t fenceRequestCount;
	uint32_t deviceMemoryRequestCount;
	uint32_t bufferRequestCount;
	uint32_t imageRequestCount;
	uint32_t eventRequestCount;
	uint32_t queryPoolRequestCount;
	uint32_t bufferViewRequestCount;
	uint32_t imageViewRequestCount;
	uint32_t layeredImageViewRequestCount;
	uint32_t pipelineCacheRequestCount;
	uint32_t pipelineLayoutRequestCount;
	uint32_t renderPassRequestCount;
	uint32_t graphicsPipelineRequestCount;
	uint32_t computePipelineRequestCount;
	uint32_t descriptorSetLayoutRequestCount;
	uint32_t samplerRequestCount;
	uint32_t descriptorPoolRequestCount;
	uint32_t descriptorSetRequestCount;
	uint32_t framebufferRequestCount;
	uint32_t commandPoolRequestCount;
	uint32_t samplerYcbcrConversionRequestCount;
	uint32_t surfaceRequestCount;
	uint32_t swapchainRequestCount;
	uint32_t displayModeRequestCount;
	uint32_t subpassDescriptionRequestCount;
	uint32_t attachmentDescriptionRequestCount;
	uint32_t descriptorSetLayoutBindingRequestCount;
	uint32_t descriptorSetLayoutBindingLimit;
	uint32_t maxImageViewMipLevels;
	uint32_t maxImageViewArrayLayers;
	uint32_t maxLayeredImageViewMipLevels;
	uint32_t maxOcclusionQueriesPerPool;
	uint32_t maxPipelineStatisticsQueriesPerPool;
	uint32_t maxTimestampQueriesPerPool;
	uint32_t maxImmutableSamplersPerDescriptorSetLayout;
} VkDeviceObjectReservationCreateInfo;

typedef enum VkPipelineMatchControl
{
	VK_PIPELINE_MATCH_CONTROL_APPLICATION_UUID_EXACT_MATCH = 0,
	VK_PIPELINE_MATCH_CONTROL_MAX_ENUM = 0x7FFFFFFF
} VkPipelineMatchControl;

typedef struct VkPipelineOfflineCreateInfo
{
	VkStructureType sType;
	const void* pNext;
	uint8_t pipelineIdentifier[VK_UUID_SIZE];
	VkPipelineMatchControl matchControl;
	VkDeviceSize poolEntrySize;
} VkPipelineOfflineCreateInfo;

typedef struct VkCommandPoolMemoryReservationCreateInfo
{
	VkStructureType sType;
	const void* pNext;
	VkDeviceSize commandPoolReservedSize;
	uint32_t commandPoolMaxCommandBuffers;
} VkCommandPoolMemoryReservationCreateInfo;

typedef struct VkCommandPoolMemoryConsumption
{
	VkStructureType sType;
	void* pNext;
	VkDeviceSize commandPoolAllocated;
	VkDeviceSize commandPoolReservedSize;
	VkDeviceSize commandBufferAllocated;
} VkCommandPoolMemoryConsumption;

typedef struct VkPhysicalDeviceVulkanSC10Properties
{
	VkStructureType sType;
	void* pNext;
	VkBool32 deviceNoDynamicHostAllocations;
	VkBool32 deviceDestroyFreesMemory;
	VkBool32 commandPoolMultipleCommandBuffersRecording;
	VkBool32 commandPoolResetCommandBuffer;
	VkBool32 commandBufferSimultaneousUse;
	VkBool32 secondaryCommandBufferNullOrImagelessFramebuffer;
	VkBool32 recycleDescriptorSetMemory;
	VkBool32 recyclePipelineMemory;
	uint32_t maxRenderPassSubpasses;
	uint32_t maxRenderPassDependencies;
	uint32_t maxSubpassInputAttachments;
	uint32_t maxSubpassPreserveAttachments;
	uint32_t maxFramebufferAttachments;
	uint32_t maxDescriptorSetLayoutBindings;
	uint32_t maxQueryFaultCount;
	uint32_t maxCallbackFaultCount;
	uint32_t maxCommandPoolCommandBuffers;
	VkDeviceSize maxCommandBufferSize;
} VkPhysicalDeviceVulkanSC10Properties;

typedef void(VKAPI_PTR* PFN_vkGetCommandPoolMemoryConsumption)(VkDevice device, VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkCommandPoolMemoryConsumption* pConsumption);

// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ifndef PFN_GetPhysicalDeviceProcAddr
typedef PFN_vkVoidFunction(VKAPI_PTR* PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, const char* pName);
#endif

typedef VkResult(VKAPI_PTR* PFN_vkSetInstanceLoaderData)(VkInstance instance, void* object);

typedef VkResult(VKAPI_PTR* PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDevice* pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr* nextGDPA);
typedef void(VKAPI_PTR* PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, const VkAllocationCallbacks* pAllocator, PFN_vkDestroyDevice destroyFunction);

typedef enum VkLoaderFeastureFlagBits
{
	VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
typedef VkFlags VkLoaderFeatureFlags;

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
typedef enum VkLayerFunction_
{
	VK_LAYER_LINK_INFO = 0,
	VK_LOADER_DATA_CALLBACK = 1,
	VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
	VK_LOADER_FEATURES = 3,
} VkLayerFunction;

typedef struct VkLayerInstanceLink_
{
	struct VkLayerInstanceLink_* pNext;
	PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
	PFN_GetPhysicalDeviceProcAddr pfnNextGetPhysicalDeviceProcAddr;
} VkLayerInstanceLink;

typedef struct
{
	VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
	const void* pNext;
	VkLayerFunction function;
	union
	{
		VkLayerInstanceLink* pLayerInfo;
		PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
		struct
		{
			PFN_vkLayerCreateDevice pfnLayerCreateDevice;
			PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
		} layerDevice;
		VkLoaderFeatureFlags loaderFeatures;
	} u;
} VkLayerInstanceCreateInfo;

#ifdef __cplusplus
}
#endif

#endif
