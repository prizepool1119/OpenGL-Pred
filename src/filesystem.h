#pragma once

#include <string>

enum class FILE_TYPE {
	MODEL,
	TEXTURE,
	SHADER,
	BASE
};

class FileSystem {
public:
	static std::string getPath(const char* fileName, FILE_TYPE type = FILE_TYPE::BASE);
private:
	static const char* modelPath;
	static const char* texturePath;
	static const char* shaderPath;
};
