#include "Object.h"
#include "Logic.h"

Object::Object(Model *model, Program &program, Texture *texture) :
		model(model),
		program(program),
		color(1.0f),
		texture(texture) {}

void Object::render(RenderContext &context) {
	context.use(*context.program);

	context.program->setMatrix("modelMatrix", modelMatrix);
	context.program->setColor(color.r, color.g, color.b);

	if(texture) {
		texture->bind();
		//program.setBool("hasTexture", true);
	} else {
		//program.setBool("hasTexture", false);
	}


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