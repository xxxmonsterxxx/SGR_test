#pragma once

// Simple Graphic Renderer (SGR) based on Vulkan library and GLFW.
// Mikhail Polestchuk, 2021, april.

#include "utils.h"

#include "WindowManager.h"
#include "PhysicalDeviceManager.h"

class SGR {
private:
	bool sgrRunning;

	std::string applicationName;
	uint8_t appVersionMajor;
	uint8_t appVersionMinor;

	WindowManager windowManager;
	bool manualWindow;
	GLFWwindow* window;

	VkInstance vulkanInstance;
	VkSurfaceKHR surface;

	PhysicalDeviceManager physDeviceManager;
	std::vector<VkQueueFlagBits> requiredFamilies;
	sgrPhysicalDevice physicalDevice;

	sgrErrCode initVulkanInstance();

public:
	SGR(std::string appName = "Simple graphic application", uint8_t appVersionMajor = 1, uint8_t appVersionMinor = 0);
	~SGR(); 

	bool isSGRRunning();
	sgrErrCode drawFrame();

	/**
	 * Init SGR and create window automatically or with arguments.
	 * 
	 * \param windowWidth
	 * \param windowHeight
	 * \param windowName
	 * \return 
	 */
	sgrErrCode init(uint32_t windowWidth = 0, uint32_t windowHeight = 0, const char *windowName = "");

	sgrErrCode destroy();

	/**
	 * Init SGR Window manually. There will be possibility to init own special window from outside.
	 * 
	 * \param newWindow
	 * \param windowName
	 * \return 
	 */
	sgrErrCode initSGRWindow(GLFWwindow* newWindow, const char* windowName);

	std::vector<sgrPhysicalDevice> getAllPhysDevInstances();
	sgrErrCode setRenderPhysicalDevice(sgrPhysicalDevice device);

	void setRequiredQueueFamilies(std::vector<VkQueueFlagBits> reqFam);
};