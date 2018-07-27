#include "Camera.h"

#include <iostream>

glm::vec3 Camera::cameraPos;
glm::vec3 Camera::cameraTarget;
glm::vec3 Camera::cameraDirection;
glm::vec3 Camera::cameraUpVector;
glm::vec3 Camera::cameraRightVector;

glm::mat4 Camera::lookAt(glm::vec3 target)
{
	cameraTarget = target;
	updateCameraVectors();

	return glm::lookAt(
		cameraPos,
		cameraTarget,
		cameraUpVector
	);
}

Camera& Camera::instance()
{
	static Camera* instance = new Camera();
	return *instance;
}

Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraRightVector = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	cameraUpVector = glm::normalize(glm::cross(cameraDirection, cameraRightVector));
}

glm::vec3 Camera::getCameraPosition()
{
	return cameraPos;
}

glm::vec3 Camera::getCameraDirection()
{
	return cameraDirection;
}

glm::vec3 Camera::getCameraTarget()
{
	return cameraTarget;
}

void Camera::printDebugInformation()
{
	system("cls");
	std::cout << "Camera position: " << "<" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ">" << std::endl;
	std::cout << "Camera direction: " << "<" << cameraDirection.x << ", " << cameraDirection.y << ", " << cameraDirection.z << ">" << std::endl;
	std::cout << "Camera target: " << "<" << cameraTarget.x << ", " << cameraTarget.y << ", " << cameraTarget.z << ">" << std::endl;
}

