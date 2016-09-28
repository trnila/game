#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	void setDimension(int width, int height) {
		view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
		projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);
	}

	const glm::mat4 getTransform() {
		return projection * view;
	}

private:
	glm::mat4 view;
	glm::mat4 projection;
};
