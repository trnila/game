#include "Camera.h"
#include <stdio.h>

Camera::Camera(Window &window) :
		window(window),
		up(0.0, 1.0, 0.0),
		target(0.0),
		v(0),
		h(0),
		width(800),
		height(600),
		zFar(50.0f),
		zNear(0.1f) {
	window.addListener(this);
	updated(window);
}

Camera::~Camera() {
	window.removeListener(this);
}

const glm::mat4 Camera::getLookAt() {
	return glm::lookAt(getPosition(), getPosition() + target, up);
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
	move(glm::normalize(target) * diff * 10.0f);
}

void Camera::backward(float diff) {
	move(-glm::normalize(target) * diff);
}

void Camera::left(float diff) {
	move(-glm::normalize(glm::cross(target, up)) * diff);
}

void Camera::right(float diff) {
	move(glm::normalize(glm::cross(target, up)) * diff);
}

glm::vec3 Camera::getDirection() {
	return target;
}

void Camera::render(RenderContext &context) {}

Object *Camera::find(int id) {
	return nullptr;
}

void Camera::transformed() {
	Transformable::transformed();
	notify();
}


