#include "OGLRenderer.h"

#include <ext/matrix_transform.hpp>

#include "ResourceManager.h"
#include "GLFW/glfw3.h"
#include "tools/Logger.h"

OGLRenderer::OGLRenderer(GLFWwindow* window)
{
    _renderData._window = window;
}

bool OGLRenderer::init(unsigned int width, unsigned int height) {
    _renderData._width = width;
    _renderData._height = height;

    /* initalize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::log(1, "%s error: failed to initialize GLAD\n", __FUNCTION__);
        return false;
    }

    if (!GLAD_GL_VERSION_4_6) {
        Logger::log(1, "%s error: failed to get at least OpenGL 4.6\n", __FUNCTION__);
        return false;
    }

    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);

    if(!_framebuffer.init(width, height))
    {
        Logger::log(1, "%s error: could not init Framebuffer\n", __FUNCTION__);
    }

    _shader = ResourceManager::loadShaders("Default", "res/shader/basic.vert", "res/shader/basic.frag");
    if(_shader == nullptr)
    {
        Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);
    }

    _chandedShader = ResourceManager::loadShaders("Changed", "res/shader/changed.vert", "res/shader/changed.frag");
    if (_chandedShader == nullptr)
    {
        Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);
    }

    _texture = ResourceManager::loadTextures("crate", "res/images/crate.png");
    if (_texture == nullptr)
    {
        Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);
    }

    _vrtexBuffer.init();
    _uniformBuffer.init();
    _userInterface.init(_renderData);

    return true;
}

void OGLRenderer::setSize(unsigned int width, unsigned int height) {
    /* handle minimize */
    if (width == 0 || height == 0) {
        return;
    }

	_framebuffer.resize(width, height);
    glViewport(0, 0, width, height);

    Logger::log(1, "%s: resized window to %dx%d\n", __FUNCTION__, width, height);
}

void OGLRenderer::uploadData(OGLMesh vertexData)
{
    _renderData._triangleCount = vertexData.vertices.size() / 3;
    _vrtexBuffer.uploadData(vertexData);
}

void OGLRenderer::draw()
{
	while (_renderData._width == 0 || _renderData._height == 0)
	{
        glfwGetFramebufferSize(_renderData._window, &_renderData._width, &_renderData._height);
        glfwWaitEvents();
	}

    static float prevFrameStartTime = 0.0f;
    float frameStartTime = glfwGetTime();

    _framebuffer.bind();

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    float t = glfwGetTime();
    glm::mat4 model = glm::mat4(1.0f);

    if(_useChangedShader == false)
    {
        _shader->use();
        _viewMatrix = glm::rotate(glm::mat4(1.0f),
            glm::radians(30.0f),
            glm::vec3(0.0f, 0.0f, 1.0f));

    }
    else
    {
        _chandedShader->use();
        _viewMatrix = glm::rotate(glm::mat4(1.0f), t,
            glm::vec3(0.0f, 0.0f, 1.0f));
    }
    
    _uniformBuffer.uploadData(_viewMatrix, _projectionMatrix);

    _texture->bind();
    _vrtexBuffer.bind();

    _vrtexBuffer.draw(GL_TRIANGLES, 0, _renderData._triangleCount * 3);
    _vrtexBuffer.unbind();
    _texture->unbind();
    _framebuffer.unbind();

    _framebuffer.drawToScreen();

    _uiGenerateTimer.start();
    _userInterface.createFrame(_renderData);
    _renderData._uiGenerateTime = _uiGenerateTimer.stop();

    _uiDrawTimer.start();
    _userInterface.render();
    _renderData._uiDrawTime = _uiDrawTimer.stop();

    _renderData._frameTime = frameStartTime - prevFrameStartTime;
    prevFrameStartTime = frameStartTime;
}

void OGLRenderer::cleanup()
{
    _shader->cleanup();
    _chandedShader->cleanup();
    _texture->cleanup();
    _vrtexBuffer.cleanup();
    _framebuffer.cleanup();
    _userInterface.cleanup();
}

void OGLRenderer::handleKeyEvents(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        _useChangedShader = !_useChangedShader;
    }
}