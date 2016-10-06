#include "Camera.h"

Camera::Camera(Window &window) : zFar(50.0f), zNear(0.1f), window(window), up(0.0, 1.0, 0.0) {
	window.addListener(this);
	updated(window);
}

Camera::~Camera() {
	window.removeListener(this);
}

const glm::mat4 Camera::getTransform() {
	return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::getPerspective() const {
	return glm::perspective(45.0f, 1.0f * width / height, zNear, zFar);
}

void Camera::rotateBy(double vert, double hor) {
	if (vert == 0 && hor == 0) {
		return;
	}

	v += vert;
	h += hor;

	setRotation(v + vert, h + hor);
	notify();
}

void Camera::move(float x, float y, float z) {
	if (x == 0 && y == 0 && z == 0) {
		return;
	}

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

	target.x = cos(v) * sin(h);
	target.y = sin(v);
	target.z = cos(v) * cos(h);

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

void Camera::forward(float diff) {
	position += glm::normalize(target) * diff;
	notify();
}

void Camera::backward(float diff) {
	position -= glm::normalize(target) * diff;
	notify();
}

void Camera::left(float diff) {
	position -= glm::normalize(glm::cross(target, up)) * diff;
	notify();
}

void Camera::right(float diff) {
	position += glm::normalize(glm::cross(target, up)) * diff;
	notify();
}


