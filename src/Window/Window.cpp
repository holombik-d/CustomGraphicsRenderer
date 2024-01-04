#include "Window.h"

bool Window::init(unsigned wight, unsigned height, std::string title)
{
	if(!glfwInit())
	{
		Logger::log(1, "$s: glfwInit error" __FUNCTION__);
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(wight, height, title.c_str(), NULL, NULL);
	if(!_window)
	{
		Logger::log(1, "$s: can`t create window" __FUNCTION__);
		glfwTerminate();
		return false;
	}

	Logger::log(1, "$s: window successfully created" __FUNCTION__);
	return true;
}

void Window::mainLoop()
{
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
	}
}

void Window::cleanup()
{
	Logger::log(1, "$s: terminating window" __FUNCTION__);
	glfwDestroyWindow(_window);
	glfwTerminate();
}
