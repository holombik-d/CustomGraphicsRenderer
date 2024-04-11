/* OpenGL */
#pragma once
#include <vector>
#include "GLFW/glfw3.h"
#include <glm.hpp>

#include "tools/Timer.h"

struct OGLVertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
};

struct OGLMesh {
	std::vector<OGLVertex> vertices;
};

struct OGLRenderData
{
	GLFWwindow* _window = nullptr;
	int _triangleCount = 0;
	int _width = 0;
	int _height = 0;

	float _frameTime = 0;
	float _uiDrawTime = 0.0f;
	float _uiGenerateTime = 0.0f;
};
