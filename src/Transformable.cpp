#include <glm/gtc/matrix_transform.hpp>
#include "Transformable.h"
#include "glm/ext.hpp"

glm::mat4 Transformable::getTransform() {
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(angle), rotateAxis);
	return model;
}

void Transformable::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void Transformable::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Transformable::rotate(float angle, float x, float y, float z) {
	this->angle = angle;
	rotateAxis = glm::vec3(x, y, z);
}

void Transformable::setAngle(float angle) {
	this->angle = angle;
}

void Transformable::addAngle(float angle) {
	this->angle += angle;
}

void Transformable::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}

void Transformable::multiplyScale(float x, float y, float z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

glm::vec3 Transformable::getScale() {
	return scale;
}

void Transformable::setPosition(glm::vec3 pos) {
	position = pos;
}

void Transformable::rotate(float angle, glm::vec3 axis) {
	this->angle = angle;
	this->rotateAxis = axis;

}

void Transformable::rotate(float angle) {
	this->angle = angle;
}

void Transformable::setScale(float s) {
	setScale(s, s, s);
}

void Transformable::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Transformable::multiplyScale(glm::vec3 scale) {
	multiplyScale(scale.x, scale.y, scale.z);
}

glm::vec3 Transformable::getPosition() {
	return position;
}

void Transformable::move(glm::vec3 pos) {
	move(pos.x, pos.y, pos.z);
}
