#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"
#include "glm/ext.hpp"

glm::mat4 Transform::getTransform() {
	glm::mat4 model(1.0f);
	model = glm::translate(model, rotatePoint);
	model = glm::rotate(model, glm::radians(angle), rotateAxis);
	model = glm::translate(model, -rotatePoint);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	return model;
}

void Transform::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void Transform::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Transform::rotate(float angle, float x, float y, float z) {
	this->angle = angle;
	rotateAxis = glm::vec3(x, y, z);
}

void Transform::setAngle(float angle) {
	this->angle = angle;
}

void Transform::addAngle(float angle) {
	this->angle += angle;
}

void Transform::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}

void Transform::setRotationPoint(float x, float y, float z) {
	rotatePoint = glm::vec3(x, y, z);
}

void Transform::multiplyScale(float x, float y, float z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

glm::vec3 Transform::getScale() {
	return scale;
}

void Transform::setPosition(glm::vec3 pos) {
	position = pos;
}

void Transform::setRotationPoint(glm::vec3 p) {
	rotatePoint = p;
}