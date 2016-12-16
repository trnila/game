#include "Object.h"

Object::Object(int id, Model *model, Program &program, Program &shadow, Texture *texture) :
		id(id),
		model(model),
		program(program),
		shadow(shadow),
		color(1.0f),
		texture(texture) {}

void Object::render(RenderContext &context) {
	Program &currentProgram = context.getStage() == RenderStage::Shadow ? shadow : program;

	context.applyShadows(currentProgram);
	currentProgram.send("modelMatrix", modelMatrix);
	currentProgram.send("offset", offset);
	currentProgram.setColor(color.r, color.g, color.b);
	GL_CHECK(glStencilFunc(GL_ALWAYS, id, 0xFF));

	model->render(context, currentProgram);
}

void Object::setColor(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

void Object::update(float diff, const glm::mat4 &parent) {
	Node::update(diff, parent);
	offset += diff;

	this->modelMatrix = parent * getTransform();
}

void Object::setColor(glm::vec3 color) {
	this->color = color;
}