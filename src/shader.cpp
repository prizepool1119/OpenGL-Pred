#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "shader.h"
#include "filesystem.h"

Shader::Shader(const char* const vertexFile, const char* const fragmentFile) {

	if (strstr(vertexFile, ".vs") == nullptr) {
		std::cout << "WARNING: Missing .vs extension to indicate vertex shader. Check if you are using the right file." << std::endl;
	}
	if (strstr(fragmentFile, ".fs") == nullptr) {
		std::cout << "WARNING: Missing .fs extension to indicate fragment shader. Check if you are using the right file." << std::endl;
	}
	compileVertexShader(vertexFile);
	compileFragmentShader(fragmentFile);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	int success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::compileVertexShader(const char* const vertexFile) {
	std::ifstream fileStream;
	std::string glslString;

	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		std::string temp = FileSystem::getPath(vertexFile, FILE_TYPE::SHADER);
		fileStream.open(temp);

		std::stringstream stringStream;
		stringStream << fileStream.rdbuf();

		fileStream.close();

		glslString = stringStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::VERTEX_SHADER::FILE_NOT_READ_SUCCESSFULLY\n" << e.what() << std::endl;
	}
	
	const char* glslCode = glslString.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &glslCode, NULL);
	glCompileShader(vertexShader);

	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAIL\n" << infoLog << std::endl;
	}
}

void Shader::compileFragmentShader(const char* const fragmentFile) {
	std::ifstream fileStream;
	std::string glslString;

	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		fileStream.open(FileSystem::getPath(fragmentFile, FILE_TYPE::SHADER));

		std::stringstream stringStream;
		stringStream << fileStream.rdbuf();

		fileStream.close();

		glslString = stringStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::FRAGMENT_SHADER::FILE_NOT_READ_SUCCESSFULLY\n" << e.what() << std::endl;
	}

	const char* glslCode = glslString.c_str();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &glslCode, NULL);
	glCompileShader(fragmentShader);

	int success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAIL\n" << infoLog << std::endl;
	}
}

void Shader::updateShader(const char* const shaderFile) {
	if (strstr(shaderFile, ".vs") == nullptr && strstr(shaderFile, ".fs") == nullptr) {
		std::cout << "WARNING::SHADER::SHADER_TYPE_NOT_RECOGNIZED" << std::endl;
		return;
	}

	if (strstr(shaderFile, ".vs") != nullptr) {
		glDetachShader(ID, vertexShader);
		compileVertexShader(shaderFile);
		glAttachShader(ID, vertexShader);
		glLinkProgram(ID);
		glDeleteShader(vertexShader);
	}

	if (strstr(shaderFile, ".fs") != nullptr) {
		glDetachShader(ID, fragmentShader);
		compileFragmentShader(shaderFile);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		glDeleteShader(fragmentShader);
	}

	int success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, glm::vec3 vec) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setMat4(const std::string& name, glm::mat4 matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}