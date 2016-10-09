#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Model.h"
#include "RenderContext.h"

class Object {
public:
	Object(Model *model, Program& program);

	glm::mat4 getTransform();
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);

	void setPosition(glm::vec3 pos);
	void rotate(float angle, float x, float y, float z);
	void setAngle(float angle);
	void addAngle(float angle);
	void multiplyScale(float x, float y, float z);
	glm::vec3 getScale();

	void setColor(float r, float g, float b);

	void setScale(float x, float y, float z);

	void setRotationPoint(float x, float y, float z);

	void setRotationPoint(glm::vec3 p);

	void render(RenderContext &context);
private:
	glm::vec3 position;
	glm::vec3 rotateAxis;
	glm::vec3 rotatePoint;
	glm::vec3 scale;
	float angle;
	Model *model;
	Program &program;
	glm::vec3 color;
};
