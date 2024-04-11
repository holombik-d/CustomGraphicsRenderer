#pragma once
#include <memory>
#include "Framebuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

#include "OGLRenderData.h"
#include "UniformBuffer.h"
#include "UserInterface.h"
#include "tools/Timer.h"

class OGLRenderer {
public:
    OGLRenderer(GLFWwindow* window);

    bool init(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void uploadData(OGLMesh vertexData);
    void draw();
    void cleanup();
    void handleKeyEvents(int key, int scancode, int action, int mods);

private:
    std::shared_ptr<Shader> _shader = nullptr;
    std::shared_ptr<Shader> _chandedShader = nullptr;
    std::shared_ptr<Texture> _texture = nullptr;
    UniformBuffer _uniformBuffer{};
    OGLRenderData _renderData;
    Framebuffer _framebuffer{};
    VertexBuffer _vrtexBuffer{};
    UserInterface _userInterface;
    Timer _uiGenerateTimer;
    Timer _uiDrawTimer;

    bool _useChangedShader = false;

    /* create identity matrix by default */
    glm::mat4 _viewMatrix = glm::mat4(1.0f);
    glm::mat4 _projectionMatrix = glm::mat4(1.0f);

};
