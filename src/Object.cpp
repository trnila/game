#include "Object.h"
#include "Logic.h"

Object::Object(Model *model, Program &program) :
		model(model),
		program(program),
		color(1.0f) {}

void Object::render(RenderContext &context) {
	context.use(program);

	program.setMatrix("modelMatrix", parent);
	program.setColor(color.r, color.g, color.b);

	model->render(context);
}

void Object::setColor(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

void Object::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	this->parent = parent * getTransform();
}

void Object::setColor(glm::vec3 color) {
	this->color = color;
}