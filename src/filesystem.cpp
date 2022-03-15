
#include "filesystem.h"
#include <iostream>

const char* FileSystem::modelPath = ".\\Assets\\Models\\";
const char* FileSystem::texturePath = ".\\Assets\\Textures\\";
const char* FileSystem::shaderPath = ".\\Shaders\\";

std::string FileSystem::getPath(const char* fileName, FILE_TYPE type) {
	if (type == FILE_TYPE::MODEL) {
		std::string str = std::string(modelPath) + fileName;
		return str;
	}
	else if (type == FILE_TYPE::TEXTURE) {
		std::string str = std::string(texturePath) + fileName;
		return str;
	}
	else if (type == FILE_TYPE::SHADER) {
		std::string str = std::string(shaderPath) + fileName;
		return str;
	}
	std::cout << "File assumed to be in base directory" << std::endl;
	return fileName;
}