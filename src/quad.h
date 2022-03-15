#pragma once
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static float data[] = {
	-0.5f, -0.5f, 0.0f, // Bottom Left
	 0.5f, -0.5f, 0.0f, // Bottom Right
	 0.5f,  0.5f, 0.0f, // Top Right
	-0.5f,  0.5f, 0.0f  // Top Left
};

static unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3
};

class Quad {
public:
	Quad(glm::vec3 position = glm::vec3(0.0f));
	void Draw();
	glm::vec3 getPosition();
private:
	unsigned int VAO, VBO, EBO;
	glm::vec3 position;
	void setupQuad();
};