#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader() = delete;
	Shader(const char* const vertexFile, const char* const fragmentFile);
	void use();
	void updateShader(const char* const shaderFile);
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec3(const std::string& name, glm::vec3 vec) const;
	void setMat4(const std::string& name, glm::mat4 matrix) const;
private:
	unsigned int vertexShader, fragmentShader;
	void compileVertexShader(const char* const vertexFile);
	void compileFragmentShader(const char* const fragmentFile);
};