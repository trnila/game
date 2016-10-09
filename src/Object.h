#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Model.h"
#include "RenderContext.h"
#include "Node.h"

class Logic;

class Object : public Node {
public:
	Object(Model *model, Program& program);
	void setColor(float r, float g, float b);
	void setColor(glm::vec3 color);
	virtual void render(RenderContext &context);
	virtual void update(float diff, const glm::mat4 &parent);

private:
	Model *model;
	Program &program;
	glm::vec3 color;
	glm::mat4 modelMatrix;
};
