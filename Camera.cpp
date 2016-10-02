#include "Camera.h"

void Camera::setDimension(int width, int height) {
	projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 10.0f);
}

const glm::mat4 Camera::getTransform() {
	glm::vec3 dir = glm::vec3(
			cos(v) * sin(h),
			sin(v),
			cos(v) * cos(h)
	);

	glm::mat4 view = glm::lookAt(position, position + dir, glm::vec3(0.0, 1.0, 0.0));
	return projection * view;
}

void Camera::rotateBy(double vert, double hor) {
	v += vert;
	h += hor;
}

void Camera::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}
