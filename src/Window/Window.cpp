#include "Window.h"

bool Window::init(unsigned wight, unsigned height, const std::string& title)
{
	if(!glfwInit())
	{
		Logger::log(1, "$s: glfwInit error" __FUNCTION__);
		return false;
	}

	glfwMakeContextCurrent(_window);
	Logger::log(1, "%s: Window successfully initialized!", __FUNCTION__);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(wight, height, title.c_str(), NULL, NULL);
	if(!_window)
	{
		Logger::log(1, "$s: can`t create window" __FUNCTION__);
		glfwTerminate();
		return false;
	}

	glfwSetWindowUserPointer(_window, this);

	initWindowCallbacks();

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

void Window::initWindowCallbacks()
{
	glfwSetWindowPosCallback(_window, [](GLFWwindow* win, int xpos, int ypos)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if(window)
			{
				window->GetInputHandler()->handleWindowMove(xpos, ypos);
			}
		});

	glfwSetWindowIconifyCallback(_window, [](GLFWwindow* win, int minimize)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if(window)
			{
				window->GetInputHandler()->handleWindowMinimize(minimize);
			}
		});

	glfwSetWindowMaximizeCallback(_window, [](GLFWwindow* win, int maximize)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if(window)
			{
				window->GetInputHandler()->handleWindowMaximize(maximize);
			}
		});

	glfwSetWindowCloseCallback(_window, [](GLFWwindow* win)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if (window)
			{
				window->GetInputHandler()->handleWindowClose();
			}
		});

	glfwSetKeyCallback(_window, [](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if (window)
			{
				window->GetInputHandler()->handleKey(key, scancode, action, mods);
			}
		});

	glfwSetMouseButtonCallback(_window, [](GLFWwindow* win, int button, int action, int mods)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if (window)
			{
				window->GetInputHandler()->handleMouseButton(button, action, mods);
			}
		});

	glfwSetCursorPosCallback(_window, [](GLFWwindow* win, double xpos, double ypos)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if (window)
			{
				window->GetInputHandler()->handleMousePosition(xpos, ypos);
			}
		});

	glfwSetCursorEnterCallback(_window, [](GLFWwindow* win, int entered)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			if (window)
			{
				window->GetInputHandler()->handleMouseEnterLeave(entered);
			}
		});
}
