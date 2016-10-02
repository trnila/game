#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera {
public:
	void setDimension(int width, int height) {
		projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);
	}

	const glm::mat4 getTransform() {
		glm::vec3 dir = glm::vec3(
				cos(v) * sin(h),
				sin(v),
				cos(v) * cos(h)
		);

		glm::mat4 view = glm::lookAt(position, position + dir, glm::vec3(0.0, 1.0, 0.0));
		return projection * view;
	}

	void rotateBy(double vert, double hor) {
		v += vert;
		h += hor;
	}

	void move(float x, float y, float z) {
		position.x += x;
		position.y += y;
		position.z += z;
	}

private:
	glm::mat4 projection;
	glm::vec3 position;

	float v, h;
};
