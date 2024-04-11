#include "Window.h"

bool Window::init(unsigned wight, unsigned height, const std::string& title)
{
	if(!glfwInit())
	{
		Logger::log(1, "$s: glfwInit error" __FUNCTION__);
		return false;
	}

	Logger::log(1, "%s: Window successfully initialized!", __FUNCTION__);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(wight, height, title.c_str(), NULL, NULL);

	if(!_window)
	{
		Logger::log(1, "$s: can`t create window" __FUNCTION__);
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, this);
	initWindowCallbacks();

	_renderer = std::make_unique<OGLRenderer>(_window);
	if (!_renderer->init(wight, height)) {
		glfwTerminate();
		Logger::log(1, "%s error: Could not init OpenGL\n", __FUNCTION__);
		return false;
	}

	_model = std::make_unique<Model>();
	_model->init();
	
	Logger::log(1, "$s: window successfully created" __FUNCTION__);
	return true;
}

void Window::mainLoop()
{
	glfwSwapInterval(1);

	_renderer->uploadData(_model->getVertexData());

	while (!glfwWindowShouldClose(_window))
	{
		_renderer->draw();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Window::cleanup()
{
	_renderer->cleanup();

	glfwDestroyWindow(_window);
	glfwTerminate();

	Logger::log(1, "$s: terminating window" __FUNCTION__);
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
				window->_renderer->handleKeyEvents(key, scancode, action, mods);
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

	glfwSetWindowSizeCallback(_window, [](GLFWwindow* win, int width, int height)
		{
			auto renderer = static_cast<OGLRenderer*>(glfwGetWindowUserPointer(win));
			if(renderer)
			{
				renderer->setSize(width, height);
			}
		});
}
