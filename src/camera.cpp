#include "camera.h"
#include <math.h>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY) {
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		Position += Front * velocity;
	if (direction == Camera_Movement::BACKWARD)
		Position -= Front * velocity;
	if (direction == Camera_Movement::RIGHT)
		Position += Right * velocity;
	if (direction == Camera_Movement::LEFT)
		Position -= Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

	//std::cout << Up.x << Up.y << Up.z << std::endl;
}