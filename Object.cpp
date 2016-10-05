#include "Object.h"

Object::Object(Model *model, Program &program) : model(model), program(program), scale(1.0f, 1.0f, 1.0f) {}

glm::mat4 Object::getTransform() {
	return
			glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotateAround)
			* glm::scale(glm::mat4(1.0f), scale);
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
	context.use(program);
	
	glm::mat4 transform = getTransform();
	UniformVariable *mvpVar = program.bindUniformVariable("modelMatrix");
	mvpVar->setData(transform);

	model->render(context);
}

void Object::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}
