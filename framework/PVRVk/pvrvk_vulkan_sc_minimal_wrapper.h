/*
\brief vulkan_sc_core_minimal.h wrapper used by PVRVk.
\file pvrvk_vulkan_sc_wrapper.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/

//!\cond NO_DOXYGEN
// clang-format off
#pragma once
#include <string>
#include "vulkan/vulkan.h"
#include "vulkan_sc_minimal/vulkan_sc_core_minimal.h"

namespace pvrvksc {

#define DEFINE_ENUM_BITWISE_OPERATORS_ULONGLONG(type_) \
inline type_ operator | (type_ lhs, type_ rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) | static_cast<unsigned long long>(rhs)); \
} \
inline type_& operator |= (type_& lhs, type_ rhs) \
{ \
	return lhs = (type_)(static_cast<unsigned long long>(lhs) | static_cast<unsigned long long>(rhs)); \
} \
inline type_ operator & (type_ lhs, type_ rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) & static_cast<unsigned long long>(rhs)); \
} \
inline type_& operator &= (type_& lhs, type_ rhs) \
{ \
	return lhs = (type_)(static_cast<unsigned long long>(lhs) & static_cast<unsigned long long>(rhs)); \
} \
inline type_ operator ^ (type_ lhs, type_ rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) ^ static_cast<unsigned long long>(rhs)); \
} \
inline type_& operator ^= (type_& lhs, type_ rhs) \
{ \
	return lhs = (type_)(static_cast<unsigned long long>(lhs) ^ static_cast<unsigned long long>(rhs)); \
} \
inline type_ operator <<(type_ lhs, unsigned long long rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) << rhs); \
} \
inline type_& operator <<=(type_& lhs, unsigned long long rhs) \
{ \
	return lhs = (type_)(static_cast<unsigned long long>(lhs) << rhs); \
} \
inline type_ operator >>(type_ lhs, unsigned long long rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) >> rhs); \
} \
inline type_& operator >>=(type_& lhs, unsigned long long rhs) \
{ \
	return lhs = (type_)(static_cast<unsigned long long>(lhs) >> rhs); \
} \
inline bool operator ==(type_ lhs, unsigned long long rhs) \
{ \
	return static_cast<unsigned long long>(lhs) == rhs; \
} \
inline bool operator !=(type_ lhs, unsigned long long rhs) \
{ \
	return static_cast<unsigned long long>(lhs) != rhs; \
} \
inline bool operator ==(unsigned long long lhs, type_ rhs) \
{ \
	return lhs == static_cast<unsigned long long>(rhs); \
}\
inline bool operator !=(unsigned long long lhs, type_ rhs) \
{ \
	return lhs != static_cast<unsigned long long>(rhs); \
}\
inline type_ operator ~(type_ lhs) \
{ \
	return (type_)(~static_cast<unsigned long long>(lhs)); \
}\
inline type_ operator *(unsigned long long lhs, type_ rhs) \
{ \
	return (type_)(lhs * static_cast<unsigned long long>(rhs)); \
}\
inline type_ operator *(type_ lhs, unsigned long long rhs) \
{ \
	return (type_)(static_cast<unsigned long long>(lhs) * rhs); \
}\

struct PipelinePoolSize: private VkPipelinePoolSize
{
	PipelinePoolSize()
	{
		setStructureType(VK_STRUCTURE_TYPE_PIPELINE_POOL_SIZE);
		setPNext(nullptr);
		setPoolEntrySize(0);
		setPoolEntryCount(0);
	}
	PipelinePoolSize(const VkPipelinePoolSize& inPipelinePoolSize): VkPipelinePoolSize(inPipelinePoolSize){}
	PipelinePoolSize(VkStructureType inSType, void const* inPNext, VkDeviceSize inPoolEntrySize, uint32_t inPoolEntryCount)
    {
		setStructureType(inSType);
		setPNext(inPNext);
		setPoolEntrySize(inPoolEntrySize);
		setPoolEntryCount(inPoolEntryCount);
	}

	inline const VkStructureType getStructureType() const { return sType; }
	inline const void* getPNext() const { return pNext; }
	inline const VkDeviceSize getPoolEntrySize() const { return poolEntrySize; }
	inline const uint32_t getPoolEntryCount() const { return poolEntryCount; }

    inline void setStructureType(const VkStructureType inSType) { this->sType = inSType; }
	inline void setPNext(void const* inPNext) { this->pNext = inPNext; }
	inline void setPoolEntrySize(VkDeviceSize inPoolEntrySize) { this->poolEntrySize = inPoolEntrySize; }
	inline void setPoolEntryCount(uint32_t inPoolEntrySize) { this->poolEntryCount = inPoolEntrySize; }
};

struct DeviceObjectReservationCreateInfo: private VkDeviceObjectReservationCreateInfo
{
    DeviceObjectReservationCreateInfo()
    {
        setSType(VK_STRUCTURE_TYPE_DEVICE_OBJECT_RESERVATION_CREATE_INFO);
        setPNext(nullptr);
        setPipelineCacheCreateInfoCount(0);
        setPPipelineCacheCreateInfos(nullptr);
        setPipelinePoolSizeCount(0);
        setPPipelinePoolSizes(nullptr);
        setSemaphoreRequestCount(0);
        setCommandBufferRequestCount(0);
        setFenceRequestCount(0);
        setDeviceMemoryRequestCount(0);
        setBufferRequestCount(0);
        setImageRequestCount(0);
        setEventRequestCount(0);
        setQueryPoolRequestCount(0);
        setBufferViewRequestCount(0);
        setImageViewRequestCount(0);
        setLayeredImageViewRequestCount(0);
        setPipelineCacheRequestCount(0);
        setPipelineLayoutRequestCount(0);
        setRenderPassRequestCount(0);
        setGraphicsPipelineRequestCount(0);
        setComputePipelineRequestCount(0);
        setDescriptorSetLayoutRequestCount(0);
        setSamplerRequestCount(0);
        setDescriptorPoolRequestCount(0);
        setDescriptorSetRequestCount(0);
        setFramebufferRequestCount(0);
        setCommandPoolRequestCount(0);
        setSamplerYcbcrConversionRequestCount(0);
        setSurfaceRequestCount(0);
        setSwapchainRequestCount(0);
        setDisplayModeRequestCount(0);
        setSubpassDescriptionRequestCount(0);
        setAttachmentDescriptionRequestCount(0);
        setDescriptorSetLayoutBindingRequestCount(0);
        setDescriptorSetLayoutBindingLimit(0);
        setMaxImageViewMipLevels(0);
        setMaxImageViewArrayLayers(0);
        setMaxLayeredImageViewMipLevels(0);
        setMaxOcclusionQueriesPerPool(0);
        setMaxPipelineStatisticsQueriesPerPool(0);
        setMaxTimestampQueriesPerPool(0);
        setMaxImmutableSamplersPerDescriptorSetLayout(0);
    }
    DeviceObjectReservationCreateInfo(const VkDeviceObjectReservationCreateInfo& vkType): VkDeviceObjectReservationCreateInfo(vkType){}

    DeviceObjectReservationCreateInfo(VkStructureType inSType, const void* inPNext, uint32_t inPipelineCacheCreateInfoCount, const VkPipelineCacheCreateInfo* inPPipelineCacheCreateInfos, uint32_t inPipelinePoolSizeCount, const VkPipelinePoolSize* inPPipelinePoolSizes, uint32_t inSemaphoreRequestCount, uint32_t inCommandBufferRequestCount, uint32_t inFenceRequestCount, uint32_t inDeviceMemoryRequestCount, uint32_t inBufferRequestCount, uint32_t inImageRequestCount, uint32_t inEventRequestCount, uint32_t inQueryPoolRequestCount, uint32_t inBufferViewRequestCount, uint32_t inImageViewRequestCount, uint32_t inLayeredImageViewRequestCount, uint32_t inPipelineCacheRequestCount, uint32_t inPipelineLayoutRequestCount, uint32_t inRenderPassRequestCount, uint32_t inGraphicsPipelineRequestCount, uint32_t inComputePipelineRequestCount, uint32_t inDescriptorSetLayoutRequestCount, uint32_t inSamplerRequestCount, uint32_t inDescriptorPoolRequestCount, uint32_t inDescriptorSetRequestCount, uint32_t inFramebufferRequestCount, uint32_t inCommandPoolRequestCount, uint32_t inSamplerYcbcrConversionRequestCount, uint32_t inSurfaceRequestCount, uint32_t inSwapchainRequestCount, uint32_t inDisplayModeRequestCount, uint32_t inSubpassDescriptionRequestCount, uint32_t inAttachmentDescriptionRequestCount, uint32_t inDescriptorSetLayoutBindingRequestCount, uint32_t inDescriptorSetLayoutBindingLimit, uint32_t inMaxImageViewMipLevels, uint32_t inMaxImageViewArrayLayers, uint32_t inMaxLayeredImageViewMipLevels, uint32_t inMaxOcclusionQueriesPerPool, uint32_t inMaxPipelineStatisticsQueriesPerPool, uint32_t inMaxTimestampQueriesPerPool, 
        uint32_t inMaxImmutableSamplersPerDescriptorSetLayout)
    {
        setSType(inSType);
        setPNext(inPNext);
        setPipelineCacheCreateInfoCount(inPipelineCacheCreateInfoCount);
        setPPipelineCacheCreateInfos(inPPipelineCacheCreateInfos);
        setPipelinePoolSizeCount(inPipelinePoolSizeCount);
        setPPipelinePoolSizes(inPPipelinePoolSizes);
        setSemaphoreRequestCount(inSemaphoreRequestCount);
        setCommandBufferRequestCount(inCommandBufferRequestCount);
        setFenceRequestCount(inFenceRequestCount);
        setDeviceMemoryRequestCount(inDeviceMemoryRequestCount);
        setBufferRequestCount(inBufferRequestCount);
        setImageRequestCount(inImageRequestCount);
        setEventRequestCount(inEventRequestCount);
        setQueryPoolRequestCount(inQueryPoolRequestCount);
        setBufferViewRequestCount(inBufferViewRequestCount);
        setImageViewRequestCount(inImageViewRequestCount);
        setLayeredImageViewRequestCount(inLayeredImageViewRequestCount);
        setPipelineCacheRequestCount(inPipelineCacheRequestCount);
        setPipelineLayoutRequestCount(inPipelineLayoutRequestCount);
        setRenderPassRequestCount(inRenderPassRequestCount);
        setGraphicsPipelineRequestCount(inGraphicsPipelineRequestCount);
        setComputePipelineRequestCount(inComputePipelineRequestCount);
        setDescriptorSetLayoutRequestCount(inDescriptorSetLayoutRequestCount);
        setSamplerRequestCount(inSamplerRequestCount);
        setDescriptorPoolRequestCount(inDescriptorPoolRequestCount);
        setDescriptorSetRequestCount(inDescriptorSetRequestCount);
        setFramebufferRequestCount(inFramebufferRequestCount);
        setCommandPoolRequestCount(inCommandPoolRequestCount);
        setSamplerYcbcrConversionRequestCount(inSamplerYcbcrConversionRequestCount);
        setSurfaceRequestCount(inSurfaceRequestCount);
        setSwapchainRequestCount(inSwapchainRequestCount);
        setDisplayModeRequestCount(inDisplayModeRequestCount);
        setSubpassDescriptionRequestCount(inSubpassDescriptionRequestCount);
        setAttachmentDescriptionRequestCount(inAttachmentDescriptionRequestCount);
        setDescriptorSetLayoutBindingRequestCount(inDescriptorSetLayoutBindingRequestCount);
        setDescriptorSetLayoutBindingLimit(inDescriptorSetLayoutBindingLimit);
        setMaxImageViewMipLevels(inMaxImageViewMipLevels);
        setMaxImageViewArrayLayers(inMaxImageViewArrayLayers);
        setMaxLayeredImageViewMipLevels(inMaxLayeredImageViewMipLevels);
        setMaxOcclusionQueriesPerPool(inMaxOcclusionQueriesPerPool);
        setMaxPipelineStatisticsQueriesPerPool(inMaxPipelineStatisticsQueriesPerPool);
        setMaxTimestampQueriesPerPool(inMaxTimestampQueriesPerPool);
        setMaxImmutableSamplersPerDescriptorSetLayout(inMaxImmutableSamplersPerDescriptorSetLayout);
    }

    inline const VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline const uint32_t getPipelineCacheCreateInfoCount() const { return pipelineCacheCreateInfoCount; }
    inline const VkPipelineCacheCreateInfo* getPPipelineCacheCreateInfos() const { return pPipelineCacheCreateInfos; }
    inline const uint32_t getPipelinePoolSizeCount() const { return pipelinePoolSizeCount; }
    inline const VkPipelinePoolSize* getPPipelinePoolSizes() const { return pPipelinePoolSizes; }
    inline const uint32_t getSemaphoreRequestCount() const { return semaphoreRequestCount; }
    inline const uint32_t getCommandBufferRequestCount() const { return commandBufferRequestCount; }
    inline const uint32_t getFenceRequestCount() const { return fenceRequestCount; }
    inline const uint32_t getDeviceMemoryRequestCount() const { return deviceMemoryRequestCount; }
    inline const uint32_t getBufferRequestCount() const { return bufferRequestCount; }
    inline const uint32_t getImageRequestCount() const { return imageRequestCount; }
    inline const uint32_t getEventRequestCount() const { return eventRequestCount; }
    inline const uint32_t getQueryPoolRequestCount() const { return queryPoolRequestCount; }
    inline const uint32_t getBufferViewRequestCount() const { return bufferViewRequestCount; }
    inline const uint32_t getImageViewRequestCount() const { return imageViewRequestCount; }
    inline const uint32_t getLayeredImageViewRequestCount() const { return layeredImageViewRequestCount; }
    inline const uint32_t getPipelineCacheRequestCount() const { return pipelineCacheRequestCount; }
    inline const uint32_t getPipelineLayoutRequestCount() const { return pipelineLayoutRequestCount; }
    inline const uint32_t getRenderPassRequestCount() const { return renderPassRequestCount; }
    inline const uint32_t getGraphicsPipelineRequestCount() const { return graphicsPipelineRequestCount; }
    inline const uint32_t getComputePipelineRequestCount() const { return computePipelineRequestCount; }
    inline const uint32_t getDescriptorSetLayoutRequestCount() const { return descriptorSetLayoutRequestCount; }
    inline const uint32_t getSamplerRequestCount() const { return samplerRequestCount; }
    inline const uint32_t getDescriptorPoolRequestCount() const { return descriptorPoolRequestCount; }
    inline const uint32_t getDescriptorSetRequestCount() const { return descriptorSetRequestCount; }
    inline const uint32_t getFramebufferRequestCount() const { return framebufferRequestCount; }
    inline const uint32_t getCommandPoolRequestCount() const { return commandPoolRequestCount; }
    inline const uint32_t getSamplerYcbcrConversionRequestCount() const { return samplerYcbcrConversionRequestCount; }
    inline const uint32_t getSurfaceRequestCount() const { return surfaceRequestCount; }
    inline const uint32_t getSwapchainRequestCount() const { return swapchainRequestCount; }
    inline const uint32_t getDisplayModeRequestCount() const { return displayModeRequestCount; }
    inline const uint32_t getSubpassDescriptionRequestCount() const { return subpassDescriptionRequestCount; }
    inline const uint32_t getAttachmentDescriptionRequestCount() const { return attachmentDescriptionRequestCount; }
    inline const uint32_t getDescriptorSetLayoutBindingRequestCount() const { return descriptorSetLayoutBindingRequestCount; }
    inline const uint32_t getDescriptorSetLayoutBindingLimit() const { return descriptorSetLayoutBindingLimit; }
    inline const uint32_t getMaxImageViewMipLevels() const { return maxImageViewMipLevels; }
    inline const uint32_t getMaxImageViewArrayLayers() const { return maxImageViewArrayLayers; }
    inline const uint32_t getMaxLayeredImageViewMipLevels() const { return maxLayeredImageViewMipLevels; }
    inline const uint32_t getMaxOcclusionQueriesPerPool() const { return maxOcclusionQueriesPerPool; }
    inline const uint32_t getMaxPipelineStatisticsQueriesPerPool() const { return maxPipelineStatisticsQueriesPerPool; }
    inline const uint32_t getMaxTimestampQueriesPerPool() const { return maxTimestampQueriesPerPool; }
    inline const uint32_t getMaxImmutableSamplersPerDescriptorSetLayout() const { return maxImmutableSamplersPerDescriptorSetLayout; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(void const* inPNext) { this->pNext = inPNext; }
    inline void setPipelineCacheCreateInfoCount(uint32_t inPipelineCacheCreateInfoCount) { this->pipelineCacheCreateInfoCount = inPipelineCacheCreateInfoCount; }
    inline void setPPipelineCacheCreateInfos(VkPipelineCacheCreateInfo const* inPPipelineCacheCreateInfos) { this->pPipelineCacheCreateInfos = inPPipelineCacheCreateInfos; }
    inline void setPipelinePoolSizeCount(uint32_t inPipelinePoolSizeCount) { this->pipelinePoolSizeCount = inPipelinePoolSizeCount; }
    inline void setPPipelinePoolSizes(VkPipelinePoolSize const* inPPipelinePoolSizes) { this->pPipelinePoolSizes = inPPipelinePoolSizes; }
    inline void setSemaphoreRequestCount(uint32_t inSemaphoreRequestCount) { this->semaphoreRequestCount = inSemaphoreRequestCount; }
    inline void setCommandBufferRequestCount(uint32_t inCommandBufferRequestCount) { this->commandBufferRequestCount = inCommandBufferRequestCount; }
    inline void setFenceRequestCount(uint32_t inFenceRequestCount) { this->fenceRequestCount = inFenceRequestCount; }
    inline void setDeviceMemoryRequestCount(uint32_t inDeviceMemoryRequestCount) { this->deviceMemoryRequestCount = inDeviceMemoryRequestCount; }
    inline void setBufferRequestCount(uint32_t inBufferRequestCount) { this->bufferRequestCount = inBufferRequestCount; }
    inline void setImageRequestCount(uint32_t inImageRequestCount) { this->imageRequestCount = inImageRequestCount; }
    inline void setEventRequestCount(uint32_t inEventRequestCount) { this->eventRequestCount = inEventRequestCount; }
    inline void setQueryPoolRequestCount(uint32_t inQueryPoolRequestCount) { this->queryPoolRequestCount = inQueryPoolRequestCount; }
    inline void setBufferViewRequestCount(uint32_t inBufferViewRequestCount) { this->bufferViewRequestCount = inBufferViewRequestCount; }
    inline void setImageViewRequestCount(uint32_t inImageViewRequestCount) { this->imageViewRequestCount = inImageViewRequestCount; }
    inline void setLayeredImageViewRequestCount(uint32_t inLayeredImageViewRequestCount) { this->layeredImageViewRequestCount = inLayeredImageViewRequestCount; }
    inline void setPipelineCacheRequestCount(uint32_t inPipelineCacheRequestCount) { this->pipelineCacheRequestCount = inPipelineCacheRequestCount; }
    inline void setPipelineLayoutRequestCount(uint32_t inPipelineLayoutRequestCount) { this->pipelineLayoutRequestCount = inPipelineLayoutRequestCount; }
    inline void setRenderPassRequestCount(uint32_t inRenderPassRequestCount) { this->renderPassRequestCount = inRenderPassRequestCount; }
    inline void setGraphicsPipelineRequestCount(uint32_t inGraphicsPipelineRequestCount) { this->graphicsPipelineRequestCount = inGraphicsPipelineRequestCount; }
    inline void setComputePipelineRequestCount(uint32_t inComputePipelineRequestCount) { this->computePipelineRequestCount = inComputePipelineRequestCount; }
    inline void setDescriptorSetLayoutRequestCount(uint32_t inDescriptorSetLayoutRequestCount) { this->descriptorSetLayoutRequestCount = inDescriptorSetLayoutRequestCount; }
    inline void setSamplerRequestCount(uint32_t inSamplerRequestCount) { this->samplerRequestCount = inSamplerRequestCount; }
    inline void setDescriptorPoolRequestCount(uint32_t inDescriptorPoolRequestCount) { this->descriptorPoolRequestCount = inDescriptorPoolRequestCount; }
    inline void setDescriptorSetRequestCount(uint32_t inDescriptorSetRequestCount) { this->descriptorSetRequestCount = inDescriptorSetRequestCount; }
    inline void setFramebufferRequestCount(uint32_t inFramebufferRequestCount) { this->framebufferRequestCount = inFramebufferRequestCount; }
    inline void setCommandPoolRequestCount(uint32_t inCommandPoolRequestCount) { this->commandPoolRequestCount = inCommandPoolRequestCount; }
    inline void setSamplerYcbcrConversionRequestCount(uint32_t inSamplerYcbcrConversionRequestCount) { this->samplerYcbcrConversionRequestCount = inSamplerYcbcrConversionRequestCount; }
    inline void setSurfaceRequestCount(uint32_t inSurfaceRequestCount) { this->surfaceRequestCount = inSurfaceRequestCount; }
    inline void setSwapchainRequestCount(uint32_t inSwapchainRequestCount) { this->swapchainRequestCount = inSwapchainRequestCount; }
    inline void setDisplayModeRequestCount(uint32_t inDisplayModeRequestCount) { this->displayModeRequestCount = inDisplayModeRequestCount; }
    inline void setSubpassDescriptionRequestCount(uint32_t inSubpassDescriptionRequestCount) { this->subpassDescriptionRequestCount = inSubpassDescriptionRequestCount; }
    inline void setAttachmentDescriptionRequestCount(uint32_t inAttachmentDescriptionRequestCount) { this->attachmentDescriptionRequestCount = inAttachmentDescriptionRequestCount; }
    inline void setDescriptorSetLayoutBindingRequestCount(uint32_t inDescriptorSetLayoutBindingRequestCount) { this->descriptorSetLayoutBindingRequestCount = inDescriptorSetLayoutBindingRequestCount; }
    inline void setDescriptorSetLayoutBindingLimit(uint32_t inDescriptorSetLayoutBindingLimit) { this->descriptorSetLayoutBindingLimit = inDescriptorSetLayoutBindingLimit; }
    inline void setMaxImageViewMipLevels(uint32_t inMaxImageViewMipLevels) { this->maxImageViewMipLevels = inMaxImageViewMipLevels; }
    inline void setMaxImageViewArrayLayers(uint32_t inMaxImageViewArrayLayers) { this->maxImageViewArrayLayers = inMaxImageViewArrayLayers; }
    inline void setMaxLayeredImageViewMipLevels(uint32_t inMaxLayeredImageViewMipLevels) { this->maxLayeredImageViewMipLevels = inMaxLayeredImageViewMipLevels; }
    inline void setMaxOcclusionQueriesPerPool(uint32_t inMaxOcclusionQueriesPerPool) { this->maxOcclusionQueriesPerPool = inMaxOcclusionQueriesPerPool; }
    inline void setMaxPipelineStatisticsQueriesPerPool(uint32_t inMaxPipelineStatisticsQueriesPerPool) { this->maxPipelineStatisticsQueriesPerPool = inMaxPipelineStatisticsQueriesPerPool; }
    inline void setMaxTimestampQueriesPerPool(uint32_t inMaxTimestampQueriesPerPool) { this->maxTimestampQueriesPerPool = inMaxTimestampQueriesPerPool; }
    inline void setMaxImmutableSamplersPerDescriptorSetLayout(uint32_t inMaxImmutableSamplersPerDescriptorSetLayout) { this->maxImmutableSamplersPerDescriptorSetLayout = inMaxImmutableSamplersPerDescriptorSetLayout; }
};

struct PipelineOfflineCreateInfo: private VkPipelineOfflineCreateInfo
{
    PipelineOfflineCreateInfo()
    {
        setSType(VK_STRUCTURE_TYPE_PIPELINE_OFFLINE_CREATE_INFO);
        setPNext(nullptr);
        memset(pipelineIdentifier, 0, sizeof(pipelineIdentifier));
        setPipelineMatchControl(VK_PIPELINE_MATCH_CONTROL_APPLICATION_UUID_EXACT_MATCH);
        setDeviceSize(0);
    }
    PipelineOfflineCreateInfo(const VkPipelineOfflineCreateInfo& vkType): VkPipelineOfflineCreateInfo(vkType){}
    PipelineOfflineCreateInfo(VkStructureType inSType, const void* inPNext, uint8_t* inPipelineIdentifier, VkPipelineMatchControl inMatchControl, VkDeviceSize inPoolEntrySize)
	{
        setSType(inSType);
        setPNext(inPNext);
        setPipelineIdentifierUUID(inPipelineIdentifier);
        setPipelineMatchControl(inMatchControl);
        setDeviceSize(inPoolEntrySize);
	}

    inline VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline uint8_t getPipelineIdentifierUUID() const { return pipelineIdentifier[0]; }
    inline VkPipelineMatchControl getPipelineMatchControl() const { return matchControl; }
    inline VkDeviceSize getDeviceSize() const { return poolEntrySize; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(const void* inPNext) { this->pNext = inPNext; }
    inline void setPipelineIdentifierUUID(uint8_t* inPipelineIdentifier) { memcpy(&this->pipelineIdentifier, &inPipelineIdentifier, VK_UUID_SIZE); }
    inline void setPipelineMatchControl(VkPipelineMatchControl inMatchControl) { this->matchControl = inMatchControl; }
    inline void setDeviceSize(VkDeviceSize inPoolEntrySize) { this->poolEntrySize = inPoolEntrySize; }
};


struct CommandPoolMemoryReservationCreateInfo: private VkCommandPoolMemoryReservationCreateInfo
{
    CommandPoolMemoryReservationCreateInfo()
	{
		setSType(VK_STRUCTURE_TYPE_COMMAND_POOL_MEMORY_RESERVATION_CREATE_INFO);
		setPNext(nullptr);
		setCommandPoolReservedSize(0);
        setCommandPoolMaxCommandBuffers(0);
	}
    CommandPoolMemoryReservationCreateInfo(const VkCommandPoolMemoryReservationCreateInfo& vkType): VkCommandPoolMemoryReservationCreateInfo(vkType){}
    CommandPoolMemoryReservationCreateInfo(VkStructureType inSType, const void* inPNext, VkDeviceSize inCommandPoolReservedSize, uint32_t inCommandPoolMaxCommandBuffers)
	{
		setSType(inSType);
        setPNext(inPNext);
        setCommandPoolReservedSize(inCommandPoolReservedSize);
        setCommandPoolMaxCommandBuffers(inCommandPoolMaxCommandBuffers);
	}

    inline VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline const VkDeviceSize getCommandPoolReservedSize() const { return commandPoolReservedSize; }
    inline const uint32_t getCommandPoolMaxCommandBuffers() const { return commandPoolMaxCommandBuffers; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(const void* inPNext) { this->pNext = inPNext; }
    inline void setCommandPoolReservedSize(VkDeviceSize inCommandPoolReservedSize) { this->commandPoolReservedSize = inCommandPoolReservedSize; }
    inline void setCommandPoolMaxCommandBuffers(uint32_t inCommandPoolMaxCommandBuffers) { this->commandPoolMaxCommandBuffers = inCommandPoolMaxCommandBuffers; }
};

struct CommandPoolMemoryConsumption: private VkCommandPoolMemoryConsumption
{
    CommandPoolMemoryConsumption()
	{
		setSType(VK_STRUCTURE_TYPE_COMMAND_POOL_MEMORY_RESERVATION_CREATE_INFO);
		setPNext(nullptr);
		setCommandPoolAllocated(0);
        setCommandPoolReservedSize(0);
        setCommandBufferAllocated(0);
	}
    CommandPoolMemoryConsumption(const VkCommandPoolMemoryConsumption& vkType): VkCommandPoolMemoryConsumption(vkType){}
    CommandPoolMemoryConsumption(VkStructureType inSType, void* inPNext, VkDeviceSize inCommandPoolAllocated, VkDeviceSize inCommandPoolReservedSize, VkDeviceSize inCommandBufferAllocated)
	{
		setSType(inSType);
        setPNext(inPNext);
        setCommandPoolAllocated(inCommandPoolAllocated);
        setCommandPoolReservedSize(inCommandPoolReservedSize);
        setCommandBufferAllocated(inCommandBufferAllocated);
	}

    inline VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline const VkDeviceSize getCommandPoolAllocated() const { return commandPoolAllocated; }
    inline const VkDeviceSize getCommandPoolReservedSize() const { return commandPoolReservedSize; }
    inline const VkDeviceSize getCommandBufferAllocated() const { return commandBufferAllocated; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(void* inPNext) { this->pNext = inPNext; }
    inline void setCommandPoolAllocated(VkDeviceSize inCommandPoolAllocated) { this->commandPoolAllocated = inCommandPoolAllocated; }
    inline void setCommandPoolReservedSize(VkDeviceSize inCommandPoolReservedSize) { this->commandPoolReservedSize = inCommandPoolReservedSize; }
    inline void setCommandBufferAllocated(VkDeviceSize inCommandBufferAllocated) { this->commandBufferAllocated = inCommandBufferAllocated; }
};

struct PhysicalDeviceVulkanSC10Properties: private VkPhysicalDeviceVulkanSC10Properties
{
    PhysicalDeviceVulkanSC10Properties()
	{
		setSType(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_SC_1_0_PROPERTIES);
		setPNext(nullptr);
        setDeviceNoDynamicHostAllocations(VK_FALSE);
        setDeviceDestroyFreesMemory(VK_FALSE);
        setCommandPoolMultipleCommandBuffersRecording(VK_FALSE);
        setCommandPoolResetCommandBuffer(VK_FALSE);
        setCommandBufferSimultaneousUse(VK_FALSE);
        setSecondaryCommandBufferNullOrImagelessFramebuffer(VK_FALSE);
        setRecycleDescriptorSetMemory(VK_FALSE);
        setInRecyclePipelineMemory(VK_FALSE);
        setMaxRenderPassSubpasses(0);
        setMaxRenderPassDependencies(0);
        setMaxSubpassInputAttachments(0);
        setMaxSubpassPreserveAttachments(0);
        setMaxFramebufferAttachments(0);
        setMaxDescriptorSetLayoutBindings(0);
        setMaxQueryFaultCount(0);
        setMaxCallbackFaultCount(0);
        setMaxCommandPoolCommandBuffers(0);
        setMaxCommandBufferSize(0);
	}
    PhysicalDeviceVulkanSC10Properties(const VkPhysicalDeviceVulkanSC10Properties& vkType): VkPhysicalDeviceVulkanSC10Properties(vkType){}
    PhysicalDeviceVulkanSC10Properties(VkStructureType inSType, void* inPNext, VkBool32 inDeviceNoDynamicHostAllocations, VkBool32 inDeviceDestroyFreesMemory, VkBool32 inCommandPoolMultipleCommandBuffersRecording, VkBool32 inCommandPoolResetCommandBuffer, VkBool32 inCommandBufferSimultaneousUse, VkBool32 inSecondaryCommandBufferNullOrImagelessFramebuffer, VkBool32 inRecycleDescriptorSetMemory, VkBool32 inRecyclePipelineMemory, uint32_t inMaxRenderPassSubpasses, uint32_t inMaxRenderPassDependencies, uint32_t inMaxSubpassInputAttachments, uint32_t inMaxSubpassPreserveAttachments, uint32_t inMaxFramebufferAttachments, uint32_t inMaxDescriptorSetLayoutBindings, uint32_t inMaxQueryFaultCount, uint32_t inMaxCallbackFaultCount, uint32_t inMaxCommandPoolCommandBuffers, VkDeviceSize inMaxCommandBufferSize)
    {
        setSType(inSType);
        setPNext(inPNext);
        setDeviceNoDynamicHostAllocations(inDeviceNoDynamicHostAllocations);
        setDeviceDestroyFreesMemory(inDeviceDestroyFreesMemory);
        setCommandPoolMultipleCommandBuffersRecording(inCommandPoolMultipleCommandBuffersRecording);
        setCommandPoolResetCommandBuffer(inCommandPoolResetCommandBuffer);
        setCommandBufferSimultaneousUse(inCommandBufferSimultaneousUse);
        setSecondaryCommandBufferNullOrImagelessFramebuffer(inSecondaryCommandBufferNullOrImagelessFramebuffer);
        setRecycleDescriptorSetMemory(inRecycleDescriptorSetMemory);
        setInRecyclePipelineMemory(inRecyclePipelineMemory);
        setMaxRenderPassSubpasses(inMaxRenderPassSubpasses);
        setMaxRenderPassDependencies(inMaxRenderPassDependencies);
        setMaxSubpassInputAttachments(inMaxSubpassInputAttachments);
        setMaxSubpassPreserveAttachments(inMaxSubpassPreserveAttachments);
        setMaxFramebufferAttachments(inMaxFramebufferAttachments);
        setMaxDescriptorSetLayoutBindings(inMaxDescriptorSetLayoutBindings);
        setMaxQueryFaultCount(inMaxQueryFaultCount);
        setMaxCallbackFaultCount(inMaxCallbackFaultCount);
        setMaxCommandPoolCommandBuffers(inMaxCommandPoolCommandBuffers);
        setMaxCommandBufferSize(inMaxCommandBufferSize);
    }

    inline VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline const VkBool32 getDeviceNoDynamicHostAllocations() const { return deviceNoDynamicHostAllocations; }
    inline const VkBool32 getDeviceDestroyFreesMemory() const { return deviceDestroyFreesMemory; }
    inline const VkBool32 getCommandPoolMultipleCommandBuffersRecording() const { return commandPoolMultipleCommandBuffersRecording; }
    inline const VkBool32 getCommandPoolResetCommandBuffer() const { return commandPoolResetCommandBuffer; }
    inline const VkBool32 getCommandBufferSimultaneousUse() const { return commandBufferSimultaneousUse; }
    inline const VkBool32 getSecondaryCommandBufferNullOrImagelessFramebuffer() const { return secondaryCommandBufferNullOrImagelessFramebuffer; }
    inline const VkBool32 getRecycleDescriptorSetMemory() const { return recycleDescriptorSetMemory; }
    inline const VkBool32 getRecyclePipelineMemory() const { return recyclePipelineMemory; }
    inline const uint32_t getMaxRenderPassSubpasses() const { return maxRenderPassSubpasses; }
    inline const uint32_t getMaxRenderPassDependencies() const { return maxRenderPassDependencies; }
    inline const uint32_t getMaxSubpassInputAttachments() const { return maxSubpassInputAttachments; }
    inline const uint32_t getMaxSubpassPreserveAttachments() const { return maxSubpassPreserveAttachments; }
    inline const uint32_t getMaxFramebufferAttachments() const { return maxFramebufferAttachments; }
    inline const uint32_t getMaxDescriptorSetLayoutBindings() const { return maxDescriptorSetLayoutBindings; }
    inline const uint32_t getMaxQueryFaultCount() const { return maxQueryFaultCount; }
    inline const uint32_t getMaxCallbackFaultCount() const { return maxCallbackFaultCount; }
    inline const uint32_t getMaxCommandPoolCommandBuffers() const { return maxCommandPoolCommandBuffers; }
    inline const VkDeviceSize getMaxCommandBufferSize() const { return maxCommandBufferSize; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(void* inPNext) { this->pNext = inPNext; }
    inline void setDeviceNoDynamicHostAllocations(VkBool32 inDeviceNoDynamicHostAllocations) { this->deviceNoDynamicHostAllocations = inDeviceNoDynamicHostAllocations; }
    inline void setDeviceDestroyFreesMemory(VkBool32 inDeviceDestroyFreesMemory) { this->deviceDestroyFreesMemory = inDeviceDestroyFreesMemory; }
    inline void setCommandPoolMultipleCommandBuffersRecording(VkBool32 inCommandPoolMultipleCommandBuffersRecording) { this->commandPoolMultipleCommandBuffersRecording = inCommandPoolMultipleCommandBuffersRecording; }
    inline void setCommandPoolResetCommandBuffer(VkBool32 inCommandPoolResetCommandBuffer) { this->commandPoolResetCommandBuffer = inCommandPoolResetCommandBuffer; }
    inline void setCommandBufferSimultaneousUse(VkBool32 inCommandBufferSimultaneousUse) { this->commandBufferSimultaneousUse = inCommandBufferSimultaneousUse; }
    inline void setSecondaryCommandBufferNullOrImagelessFramebuffer(VkBool32 inSecondaryCommandBufferNullOrImagelessFramebuffer) { this->secondaryCommandBufferNullOrImagelessFramebuffer = inSecondaryCommandBufferNullOrImagelessFramebuffer; }
    inline void setRecycleDescriptorSetMemory(VkBool32 inRecycleDescriptorSetMemory) { this->recycleDescriptorSetMemory = inRecycleDescriptorSetMemory; }
    inline void setInRecyclePipelineMemory(VkBool32 inRecyclePipelineMemory) { this->recyclePipelineMemory = inRecyclePipelineMemory; }
    inline void setMaxRenderPassSubpasses(uint32_t inMaxRenderPassSubpasses) { this->maxRenderPassSubpasses = inMaxRenderPassSubpasses; }
    inline void setMaxRenderPassDependencies(uint32_t inMaxRenderPassDependencies) { this->maxRenderPassDependencies = inMaxRenderPassDependencies; }
    inline void setMaxSubpassInputAttachments(uint32_t inMaxSubpassInputAttachments) { this->maxSubpassInputAttachments = inMaxSubpassInputAttachments; }
    inline void setMaxSubpassPreserveAttachments(uint32_t inMaxSubpassPreserveAttachments) { this->maxSubpassPreserveAttachments = inMaxSubpassPreserveAttachments; }
    inline void setMaxFramebufferAttachments(uint32_t inMaxFramebufferAttachments) { this->maxFramebufferAttachments = inMaxFramebufferAttachments; }
    inline void setMaxDescriptorSetLayoutBindings(uint32_t inMaxDescriptorSetLayoutBindings) { this->maxDescriptorSetLayoutBindings = inMaxDescriptorSetLayoutBindings; }
    inline void setMaxQueryFaultCount(uint32_t inMaxQueryFaultCount) { this->maxQueryFaultCount = inMaxQueryFaultCount; }
    inline void setMaxCallbackFaultCount(uint32_t inMaxCallbackFaultCount) { this->maxCallbackFaultCount = inMaxCallbackFaultCount; }
    inline void setMaxCommandPoolCommandBuffers(uint32_t inMaxCommandPoolCommandBuffers) { this->maxCommandPoolCommandBuffers = inMaxCommandPoolCommandBuffers; }
    inline void setMaxCommandBufferSize(VkDeviceSize inMaxCommandBufferSize) { this->maxCommandBufferSize = inMaxCommandBufferSize; }
};

struct LayerInstanceLink_: private VkLayerInstanceLink_
{
    LayerInstanceLink_()
	{
		setPNext(nullptr);
		setPfnNextGetInstanceProcAddr(nullptr);
        setInPfnNextGetPhysicalDeviceProcAddr(nullptr);
    }
    LayerInstanceLink_(const VkLayerInstanceLink_& vkType): VkLayerInstanceLink_(vkType){}
    LayerInstanceLink_(VkLayerInstanceLink_* pNext, PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr, PFN_GetPhysicalDeviceProcAddr pfnNextGetPhysicalDeviceProcAddr)
    {
        setPNext(pNext);
        setPfnNextGetInstanceProcAddr(pfnNextGetInstanceProcAddr);
        setInPfnNextGetPhysicalDeviceProcAddr(pfnNextGetPhysicalDeviceProcAddr);
    }

    inline const void* getPNext() const { return pNext; }
    inline PFN_vkGetInstanceProcAddr getPfnNextGetInstanceProcAddr() const { return pfnNextGetInstanceProcAddr; }
    inline PFN_GetPhysicalDeviceProcAddr getPfnNextGetPhysicalDeviceProcAddr() const { return pfnNextGetPhysicalDeviceProcAddr; }

    inline void setPNext(VkLayerInstanceLink_* inPNext) { this->pNext = inPNext; }
    inline void setPfnNextGetInstanceProcAddr(PFN_vkGetInstanceProcAddr inPfnNextGetInstanceProcAddr) { this->pfnNextGetInstanceProcAddr = inPfnNextGetInstanceProcAddr; }
    inline void setInPfnNextGetPhysicalDeviceProcAddr(PFN_GetPhysicalDeviceProcAddr inPfnNextGetPhysicalDeviceProcAddr) { this->pfnNextGetPhysicalDeviceProcAddr = inPfnNextGetPhysicalDeviceProcAddr; }
};

struct LayerInstanceCreateInfo: private VkLayerInstanceCreateInfo
{
    LayerInstanceCreateInfo()
	{
		setSType(VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);
		setPNext(nullptr);
        setFunction(VK_LAYER_LINK_INFO);
        setPLayerInfo(nullptr);
    }
    LayerInstanceCreateInfo(const VkLayerInstanceCreateInfo& vkType): VkLayerInstanceCreateInfo(vkType){}
    LayerInstanceCreateInfo(VkStructureType inSType, void* inPNext, VkLayerFunction inFunction)
    {
        setSType(inSType);
        setPNext(inPNext);
        setFunction(inFunction);
        // Union member will need to be defined with an extra setter to avoid overwritting previous values assigned.
    }

    inline VkStructureType getSType() const { return sType; }
    inline const void* getPNext() const { return pNext; }
    inline VkLayerFunction getFunction() const { return function; }
    inline const VkLayerInstanceLink* getPLayerInfo() const { return u.pLayerInfo; }
    inline const PFN_vkSetInstanceLoaderData getPfnSetInstanceLoaderData() const { return u.pfnSetInstanceLoaderData; }
    inline const PFN_vkLayerCreateDevice getPfnLayerCreateDevice() const { return u.layerDevice.pfnLayerCreateDevice; }
    inline const PFN_vkLayerDestroyDevice getPfnLayerDestroyDevice() const { return u.layerDevice.pfnLayerDestroyDevice; }
    inline const VkLoaderFeatureFlags getLoaderFeatures() const { return u.loaderFeatures; }

    inline void setSType(VkStructureType inSType) { this->sType = inSType; }
    inline void setPNext(void* inPNext) { this->pNext = inPNext; }
    inline void setFunction(VkLayerFunction inFunction) { this->function = inFunction; }
    inline void setPLayerInfo(VkLayerInstanceLink* inPLayerInfo) { this->u.pLayerInfo = inPLayerInfo; }
    inline void setPfnSetInstanceLoaderData(PFN_vkSetInstanceLoaderData inPfnSetInstanceLoaderData) { this->u.pfnSetInstanceLoaderData = inPfnSetInstanceLoaderData; }
    inline void setPfnLayerCreateDevice(PFN_vkLayerCreateDevice inPfnLayerCreateDevice) { this->u.layerDevice.pfnLayerCreateDevice = inPfnLayerCreateDevice; }
    inline void setPfnLayerDestroyDevice(PFN_vkLayerDestroyDevice inPfnLayerDestroyDevice) { this->u.layerDevice.pfnLayerDestroyDevice = inPfnLayerDestroyDevice; }
    inline void setLoaderFeatures(VkLoaderFeatureFlags inLoaderFeatures) { this->u.loaderFeatures = inLoaderFeatures; }
};

} // namespace pvrvksc
// clang-format on
//!\endcond
