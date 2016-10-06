#include "Camera.h"

Camera::Camera(Window &window) : zFar(50.0f), zNear(0.1f), window(window) {
	window.addListener(this);
	updated(window);
}

Camera::~Camera() {
	window.removeListener(this);
}

const glm::mat4 Camera::getTransform() {
	glm::vec3 dir = glm::vec3(
			cos(v) * sin(h),
			sin(v),
			cos(v) * cos(h)
	);

	return glm::lookAt(position, position + dir, glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Camera::getPerspective() const {
	return glm::perspective(45.0f, 1.0f * width / height, zNear, zFar);
}

void Camera::rotateBy(double vert, double hor) {
	v += vert;
	h += hor;

	notify();
}

void Camera::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
	notify();
}

void Camera::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	notify();
}

void Camera::setRotation(float vert, float hor) {
	v = vert;
	h = hor;
	notify();
}

void Camera::setZFar(float zFar) {
	this->zFar = zFar;
	notify();
}

void Camera::setZNear(float zNear) {
	this->zNear = zNear;
	notify();
}

void Camera::updated(Window &camera) {
	width = camera.getWidth();
	height = camera.getHeight();
	notify();
}
