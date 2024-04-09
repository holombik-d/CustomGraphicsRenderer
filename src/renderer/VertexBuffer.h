#pragma once
#include <vector>
#include <glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OGLRenderData.h"

class VertexBuffer {
public:
    void init();
    void uploadData(OGLMesh vertexData);
    void bind();
    void unbind();
    void draw(GLuint mode, unsigned int start, unsigned int num);
    void cleanup();

private:
    GLuint _VAO = 0;
    GLuint _vertexVBO = 0;
};