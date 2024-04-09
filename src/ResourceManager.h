#pragma once
#include <map>
#include <memory>
#include <string>

#include "renderer/Shader.h"
#include "renderer/Texture.h"

class ResourceManager
{
public:
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();

	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<Shader> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<Shader> getShadersProgram(const std::string& shaderName);

	static std::shared_ptr<Texture> loadTextures(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<Texture> getTexture(const std::string& textureName);

private:
	static std::string getFileString(const std::string& relativeFilePath);

	typedef std::map<const std::string, std::shared_ptr<Shader>> ShaderProgramsMap;
	static ShaderProgramsMap _shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Texture>> TexturesMap;
	static TexturesMap _textures;

	static std::string _path;
};
