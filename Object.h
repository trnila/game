
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Model.h"

class Object {
public:
	glm::mat4 getTransform();
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void setAngle(float angle);
	void addAngle(float angle);

	Model *renderable;

private:
	glm::vec3 position;
	glm::vec3 rotateAround;
	float angle;
};