#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Model.h"
#include "RenderContext.h"
#include "Node.h"
#include "Texture.h"

class Logic;

class Object : public Node {
public:
	Object(int id, Model *model, Program &program, Program &shadow, Texture *texture);

	void setColor(float r, float g, float b);
	void setColor(glm::vec3 color);
	virtual void render(RenderContext &context);
	virtual void update(float diff, const glm::mat4 &parent);

	int getId() {
		return id;
	}

	virtual Object* find(int id) {
		if (this->id == id) {
			return this;
		}
		return nullptr;
	}

private:
	int id;
	Model *model;
	Program &program, &shadow;
	glm::vec3 color;
	glm::mat4 modelMatrix;
	Texture *texture;
};
