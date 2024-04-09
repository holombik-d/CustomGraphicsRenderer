#include "OGLRenderer.h"

#include "ResourceManager.h"
#include "GLFW/glfw3.h"
#include "tools/Logger.h"

bool OGLRenderer::init(unsigned int width, unsigned int height) {

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

    _texture = ResourceManager::loadTextures("crate", "res/images/crate.png");
    if (_texture == nullptr)
    {
        Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);
    }

    _vrtexBuffer.init();

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
    _triangleCount = vertexData.vertices.size() / 3;
    _vrtexBuffer.uploadData(vertexData);
}

void OGLRenderer::draw()
{
    _framebuffer.bind();

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    _shader->use();
    _texture->bind();
    _vrtexBuffer.bind();

    _vrtexBuffer.draw(GL_TRIANGLES, 0, _triangleCount * 3);
    _vrtexBuffer.unbind();
    _texture->unbind();
    _framebuffer.unbind();

    _framebuffer.drawToScreen();
}

void OGLRenderer::cleanup()
{
    _shader->cleanup();
    _texture->cleanup();
    _vrtexBuffer.cleanup();
    _framebuffer.cleanup();
}
