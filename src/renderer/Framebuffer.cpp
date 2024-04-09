#include "Framebuffer.h"
#include "tools/Logger.h"

bool Framebuffer::init(unsigned int width, unsigned int height) {
    _bufferWidth = width;
    _bufferHeight = height;

    glGenFramebuffers(1, &_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _buffer);
    glEnable(GL_FRAMEBUFFER_SRGB);

    /* color texture */
    glGenTextures(1, &_colorTex);
    glBindTexture(GL_TEXTURE_2D, _colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _colorTex, 0);
    Logger::log(1, "%s: added color buffer\n", __FUNCTION__);

    /* render buffer as depth buffer */
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    Logger::log(1, "%s: added depth renderbuffer\n", __FUNCTION__);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return checkComplete();
}

void Framebuffer::cleanup() {
    unbind();

    glDeleteTextures(1, &_colorTex);
    glDeleteRenderbuffers(1, &_depthBuffer);
    glDeleteFramebuffers(1, &_buffer);
}

bool Framebuffer::resize(unsigned int newWidth, unsigned int newHeight) {
    Logger::log(1, "%s: resizing framebuffer from %dx%d to %dx%d\n", __FUNCTION__, _bufferWidth, _bufferHeight, newWidth, newHeight);
    _bufferWidth = newWidth;
    _bufferHeight = newHeight;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDeleteTextures(1, &_colorTex);
    glDeleteRenderbuffers(1, &_depthBuffer);
    glDeleteFramebuffers(1, &_buffer);

    return init(newWidth, newHeight);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _buffer);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::drawToScreen() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _buffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, _bufferWidth, _bufferHeight, 0, 0, _bufferWidth, _bufferHeight,
        GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

bool Framebuffer::checkComplete() {
    glBindFramebuffer(GL_FRAMEBUFFER, _buffer);

    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (result != GL_FRAMEBUFFER_COMPLETE) {
        Logger::log(1, "%s error: framebuffer is NOT complete\n", __FUNCTION__);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Logger::log(1, "%s: framebuffer is complete\n", __FUNCTION__);
    return true;
}