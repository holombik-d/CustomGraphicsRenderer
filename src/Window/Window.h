#pragma once
#include "renderer/OGLRenderer.h"
#include <string>

#include "GLFW/glfw3.h"
#include "model/Model.h"
#include "tools/Logger.h"
#include "tools/InputHandler.h"
#include "Window/Window.h"

class Window
{
public:
	bool init(unsigned int wight, unsigned int height, const std::string& title);
	void mainLoop();
	void cleanup();

	void SetInputHandler(InputHandler* handler) { _inputHandler = handler; }
	InputHandler* GetInputHandler() const { return _inputHandler; }

private:
	GLFWwindow* _window = nullptr;
	InputHandler* _inputHandler = nullptr;
	std::unique_ptr<OGLRenderer> _renderer;
	std::unique_ptr<Model> _model;
	void initWindowCallbacks();
};