#include "Object.h"

Object::Object(Model *model) : model(model) {}

glm::mat4 Object::getTransform() {
	return glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotateAround);
}

void Object::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void Object::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Object::rotate(float angle, float x, float y, float z) {
	this->angle = angle;
	rotateAround = glm::vec3(x, y, z);
}

void Object::setAngle(float angle) {
	this->angle = angle;
}

void Object::addAngle(float angle) {
	this->angle += angle;
}

void Object::render(RenderContext &context) {
	model->render(context);
}
