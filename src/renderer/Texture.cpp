#include "Texture.h"

Texture::Texture(const GLuint width, const GLuint height, const unsigned char* data, const unsigned channels,
	const GLenum filter, const GLenum wrapMode) : _width(width), _height(height)
{
	switch (channels)
	{
	case 4:
		_mode = GL_RGBA;
		break;
	case 3:
		_mode = GL_RGB;
		break;
	default:
		_mode = GL_RGBA;
		break;
	}

	glGenTextures(1, &_ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, 0, _mode, _width, _height, 0, _mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& texture)
{
	_ID = texture._ID;
	texture._ID = 0;
	_mode = texture._mode;
	_width = texture._width;
	_height = texture._height;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_ID);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, _ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::cleanup() const
{
	glDeleteTextures(1, &_ID);
}

unsigned Texture::getWidth() const
{
	return _width;
}

unsigned Texture::getHeight() const
{
	return _height;
}
