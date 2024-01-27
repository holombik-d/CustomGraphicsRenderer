#include "tools/InputHandler.h"

#include "Logger.h"
#include "GLFW/glfw3.h"

void InputHandler::handleWindowMove(int xpos, int ypos)
{
	Logger::log(1, "%s: Window has been moved to %i/%i\n", __FUNCTION__, xpos, ypos);
}

void InputHandler::handleWindowMinimize(bool minimized)
{
	if (minimized) {
		Logger::log(1, "%s: Window has been minimized\n", __FUNCTION__);
	}
	else {
		Logger::log(1, "%s: Window has been restored\n", __FUNCTION__);
	}
}

void InputHandler::handleWindowMaximize(bool maximized)
{
	if (maximized) {
		Logger::log(1, "%s: Window has been maximized\n", __FUNCTION__);
	}
	else {
		Logger::log(1, "%s: Window has been restored\n", __FUNCTION__);
	}
}

void InputHandler::handleWindowClose()
{
	Logger::log(-1, "%s: Window successfully initialized!", __FUNCTION__);
}

void InputHandler::handleKey(int key, int scancode, int action, int mods)
{
	std::string actionName;
	switch (action) {
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	const char* keyName = glfwGetKeyName(key, 0);
	Logger::log(1, "%s: key %s (key %i, scancode %i) %s\n", __FUNCTION__, keyName, key, scancode, actionName.c_str());
}

void InputHandler::handleMouseButton(int button, int action, int mods)
{
	std::string actionName;
	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	std::string mouseButtonName;
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButtonName = "left";
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButtonName = "middle";
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButtonName = "right";
		break;
	default:
		mouseButtonName = "other";
		break;
	}

	Logger::log(1, "%s: %s mouse button (%i) %s\n", __FUNCTION__, mouseButtonName.c_str(), button, actionName.c_str());
}

void InputHandler::handleMousePosition(double xpos, double ypos)
{
	Logger::log(1, "%s: Mouse is at position %lf%lf\n", __FUNCTION__, xpos, ypos);
}

void InputHandler::handleMouseEnterLeave(bool entered)
{
	if(entered)
	{
		Logger::log(1, "%s: Mouse is entered window\n", __FUNCTION__);
	}
	else
	{
		Logger::log(1, "%s: Mouse is leave window\n", __FUNCTION__);
	}
}
