#pragma once
#include "glad/glad.h"

class Texture
{
public:
	Texture(const GLuint width, const GLuint height, const unsigned char* data,
		const unsigned int channels = 4, const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
	Texture() = delete;
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&& texture) = delete;
	Texture(Texture&& texture);
	~Texture();

	void bind() const;
	void unbind() const;
	void cleanup() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:
	GLuint _ID;
	GLuint _mode;
	unsigned int _width;
	unsigned int _height;
};