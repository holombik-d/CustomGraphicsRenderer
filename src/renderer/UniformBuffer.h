#pragma once
#include <glm.hpp>
#include "glad/glad.h"

class UniformBuffer
{
public:
	void init();
	void uploadData(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void cleanup();

private:
	GLuint _uboBuffer = 0;
};
