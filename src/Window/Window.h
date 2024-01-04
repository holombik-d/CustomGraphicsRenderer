#pragma once
#include <string>

#include "GLFW/glfw3.h"
#include "tools/Logger.h"
#include "Window/Window.h"

class Window
{
public:
	bool init(unsigned int wight, unsigned int height, std::string title);
	void mainLoop();
	void cleanup();

private:
	GLFWwindow* _window = nullptr;
};