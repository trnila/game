#include "Camera.h"

Camera::Camera() : zFar(50.0f), zNear(0.1f) {}

void Camera::setViewportSize(int width, int height) {
	this->width = width;
	this->height = height;
}

const glm::mat4 Camera::getTransform() {
	glm::mat4 projection = glm::perspective(45.0f, 1.0f * width / height, zNear, zFar);

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

void Camera::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::setRotation(float vert, float hor) {
	v = vert;
	h = hor;
}

void Camera::setZFar(float zFar) {
	Camera::zFar = zFar;
}

void Camera::setZNear(float zNear) {
	Camera::zNear = zNear;
}
