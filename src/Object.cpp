#include "Object.h"
#include "Logic.h"

Object::Object(Model *model, Program &program) :
		position(0, 0, 0),
		rotateAxis(0, 0, 0),
		rotatePoint(0, 0, 0),
		scale(1.0f, 1.0f, 1.0f),
		angle(0),
		model(model),
		program(program),
		color(1.0f),
		logic(nullptr) {}

Object::~Object() {
	if (logic) {
		delete logic;
	}
}

glm::mat4 Object::getTransform() {
	glm::mat4 model(1.0f);
	model = glm::translate(model, rotatePoint);
	model = glm::rotate(model, glm::radians(angle), rotateAxis);
	model = glm::translate(model, -rotatePoint);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	return model;
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
	rotateAxis = glm::vec3(x, y, z);
}

void Object::setAngle(float angle) {
	this->angle = angle;
}

void Object::addAngle(float angle) {
	this->angle += angle;
}

void Object::render(RenderContext &context) {
	context.use(program);

	program.setMatrix("modelMatrix", getTransform());
	program.setColor(color.r, color.g, color.b);

	model->render(context);
}

void Object::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}

void Object::setColor(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

void Object::setRotationPoint(float x, float y, float z) {
	rotatePoint = glm::vec3(x, y, z);
}

void Object::multiplyScale(float x, float y, float z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;

}

glm::vec3 Object::getScale() {
	return scale;
}

void Object::setPosition(glm::vec3 pos) {
	position = pos;
}

void Object::setRotationPoint(glm::vec3 p) {
	rotatePoint = p;
}

void Object::update(float diff) {
	if (logic) {
		logic->update(diff);
	}
}

void Object::setColor(glm::vec3 color) {
	this->color = color;
}
