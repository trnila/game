#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	void setDimension(int width, int height) {
		view = glm::lookAt(pos, glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
		projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);
	}

	const glm::mat4 getTransform() {
		view = glm::lookAt(pos, pos + dir, glm::vec3(0.0, 1.0, 0.0));
		return projection * view;
	}

	glm::vec3 pos = glm::vec3(0, 2, 0);
	glm::vec3 dir = glm::vec3(0, 0, -4);

private:
	glm::mat4 view;
	glm::mat4 projection;
};
