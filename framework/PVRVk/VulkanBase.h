/*!
\brief Vulkan base class for all Vulkan SDK samples
\file PVRVk/VulkanBase.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#pragma once
#include "PVRShell/Shell.h"

/// <summary>Class implementing only Shell::preInitApplication method.</summary>
class VulkanBase : public pvr::Shell
{
	/// <summary>IMPLEMENT THIS FUNCTION IN YOUR APPLICATION CLASS. This event is called before application start.</summary>
	/// <returns>When implementing, return a suitable error code to signify failure. If pvr::Result::Success is not
	/// returned , the Shell will detect that, clean up, and exit.</returns>
	virtual pvr::Result preInitApplication();
};