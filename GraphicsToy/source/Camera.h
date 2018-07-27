#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



class Camera final
{
public:
	static glm::mat4 lookAt(glm::vec3 target);
	static Camera& instance();
	static void printDebugInformation();

	static glm::vec3 getCameraPosition();
	static glm::vec3 getCameraDirection();
	static glm::vec3 getCameraTarget();


private:
	Camera();

	static void updateCameraVectors();
	
	// Deleted functions
	Camera(const Camera &old) = delete;
	const Camera &operator=(const Camera &old) = delete;

public:
	static glm::vec3 cameraPos;
private:
	static glm::vec3 cameraTarget;
	static glm::vec3 cameraDirection;
	static glm::vec3 cameraUpVector;
	static glm::vec3 cameraRightVector;
};