#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	Shader() = delete;
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&& program) noexcept;
	Shader(Shader&& program) noexcept;

	bool isCompiled();
	void use() const;
	void cleanup();

private:
	bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	bool _isCompiled = false;
	GLuint _ID = 0;
};
