#include "Shader.h"
#include <iostream>
#include <ostream>

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint vertexShaderID;
	if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
	{
		return;
	}

	GLuint fragmentShaderID;
	if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
	{
		glDeleteShader(vertexShaderID);
		return;
	}

	_ID = glCreateProgram();
	glAttachShader(_ID, vertexShaderID);
	glAttachShader(_ID, fragmentShaderID);
	glLinkProgram(_ID);

	GLint success;
	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
	}
	else
	{
		_isCompiled = true;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
	glDeleteProgram(_ID);
}

Shader& Shader::operator=(Shader&& program) noexcept
{
	glDeleteProgram(_ID);
	_ID = program._ID;
	_isCompiled = program._isCompiled;

	program._ID = 0;
	program._isCompiled = false;

	return *this;
}

Shader::Shader(Shader&& program) noexcept
{
	_ID = program._ID;
	_isCompiled = program._isCompiled;

	program._ID = 0;
	program._isCompiled = false;
}

bool Shader::isCompiled()
{
	return _isCompiled;
}

void Shader::use() const
{
	glUseProgram(_ID);
}

void Shader::cleanup()
{
	glDeleteShader(_ID);
}

bool Shader::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* code = source.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLchar infolog(1024);
		glGetProgramInfoLog(shaderID, 1024, nullptr, &infolog);
		return false;
	}
	return true;
}
