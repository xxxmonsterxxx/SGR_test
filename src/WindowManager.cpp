#include "WindowManager.h"
#include "SGR.h"
#include <stb_image.h>
#include "ico.h"


void WindowManager::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	if (width == 0 || height == 0)
		app->windowMinimized = true;
	else {
		app->windowResized = true;
		app->windowMinimized = false;
		if (app->getParrentSGRptr()) {
			app->requestUpdateSwapChain();
			app->getParrentSGRptr()->drawFrame();
		}
	}
}

void WindowManager::windowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	auto app = reinterpret_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	app->windowResized = true;
	app->windowMinimized = false;
	if (app->getParrentSGRptr()) {
		app->requestUpdateSwapChain();
		app->getParrentSGRptr()->drawFrame();
	}
}

WindowManager* WindowManager::instance = nullptr;

WindowManager::WindowManager() { ; }
WindowManager::~WindowManager() { ; }

WindowManager* WindowManager::get()
{
	if (instance == nullptr) {
		instance = new WindowManager();
		return instance;
	}
	else {
		return instance;
	}
}

SgrErrCode WindowManager::init(uint32_t windowWidth, uint32_t windowHeight, const char* windowName)
{
	if (windowWidth != 0)
		this->width = windowWidth;
	if (windowHeight != 0)
		this->height = windowHeight;
	if (std::string(windowName).length() != 0)
		this->name = std::string(windowName);

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	glfwSetWindowPosCallback(window, windowPosCallback);
	glfwSetWindowAspectRatio(window, 1, 1);

	GLFWimage icons[1];
	icons[0].height = 48;
	icons[0].width = 48;
	icons[0].pixels = SGRLogo;
	glfwSetWindowIcon(window, 1, icons);

	if (window == nullptr)
		return sgrInitWindowError;

	return sgrOK;
}

SgrErrCode WindowManager::init(GLFWwindow* newWindow, const char* windowName)
{
	if (newWindow == nullptr) {
		return sgrBadPointer;
	}

	glfwGetWindowSize(newWindow, (int*)(&width), (int*)&(height));
	this->name = std::string(windowName);
	window = newWindow;

	return sgrOK;
}

void WindowManager::setAspectRatio(uint8_t x, uint8_t y)
{
	glfwSetWindowAspectRatio(window, x, y);
}

void WindowManager::requestUpdateSwapChain()
{
	SwapChainManager::instance->reinitSwapChain();
	windowResized = false;
}

void WindowManager::destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	_parrentSgr = nullptr;
	delete instance;
}
