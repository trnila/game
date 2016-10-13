#include "Object.h"
#include "Logic.h"
#include "Texture.h"

Object::Object(Model *model, Program &program) :
		model(model),
		program(program),
		color(1.0f) {
	this->texture = new Texture("resources/cube.png");

}

void Object::render(RenderContext &context) {
	context.use(program);

	program.setMatrix("modelMatrix", modelMatrix);
	program.setColor(color.r, color.g, color.b);

	this->texture->bind();
	model->render(context);
}

void Object::setColor(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

void Object::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	this->modelMatrix = parent * getTransform();
}

void Object::setColor(glm::vec3 color) {
	this->color = color;
}