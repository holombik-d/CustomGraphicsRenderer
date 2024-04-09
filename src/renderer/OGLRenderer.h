#pragma once
#include <memory>
#include "Framebuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

#include "OGLRenderData.h"

class OGLRenderer {
public:
    bool init(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void uploadData(OGLMesh vertexData);
    void draw();
    void cleanup();

private:
    std::shared_ptr<Shader> _shader = nullptr;
    Framebuffer _framebuffer{};
    std::shared_ptr<Texture> _texture = nullptr;
    VertexBuffer _vrtexBuffer{};

    int _triangleCount = 0;

};