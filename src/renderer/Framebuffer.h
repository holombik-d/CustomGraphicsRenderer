#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer {
public:
    bool init(unsigned int width, unsigned int height);
    bool resize(unsigned int newWidth, unsigned int newHeight);
    void bind();
    void unbind();
    void drawToScreen();
    void cleanup();

private:
    unsigned int _bufferWidth = 640;
    unsigned int _bufferHeight = 480;
    GLuint _buffer = 0;
    GLuint _colorTex = 0;
    GLuint _depthBuffer = 0;

    bool checkComplete();
};