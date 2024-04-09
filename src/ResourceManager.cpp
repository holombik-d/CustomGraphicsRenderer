#include "ResourceManager.h"

#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"


ResourceManager::ShaderProgramsMap ResourceManager::_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::_textures;
std::string ResourceManager::_path;

void ResourceManager::setExecutablePath(const std::string& executablePath)
{
	std::size_t found = executablePath.find_last_of("/\\");
	_path = executablePath.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
	_shaderPrograms.clear();
	_textures.clear();
}

std::shared_ptr<Shader> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath,
	const std::string& fragmentPath)
{
	std::string vertexShaderAsString = getFileString(vertexPath);
	if(vertexShaderAsString.empty())
	{
		return nullptr;
	}

	std::string fragmentShaderAsString = getFileString(fragmentPath);
	if(fragmentShaderAsString.empty())
	{
		return nullptr;
	}

	std::shared_ptr<Shader>& newShader = _shaderPrograms.emplace(shaderName, std::make_shared<Shader>(vertexShaderAsString, fragmentShaderAsString)).first->second;
	if(newShader->isCompiled())
	{
		return newShader;
	}

	return nullptr;
}

std::shared_ptr<Texture> ResourceManager::loadTextures(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if(!pixels)
	{
		return nullptr;
	}

	std::shared_ptr<Texture> newTexture = _textures.emplace(textureName, std::make_shared<Texture>(width, height, pixels,
		channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}


std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = _textures.find(textureName);
	if(it != _textures.end())
	{
		return it->second;
	}

	return nullptr;
}

std::shared_ptr<Shader> ResourceManager::getShadersProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = _shaderPrograms.find(shaderName);
	if(it != _shaderPrograms.end())
	{
		return it->second;
	}

	return nullptr;
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream file;
	file.open(_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if(!file.is_open())
	{
		return std::string();
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
