#pragma once

#include <glm/mat4x4.hpp>

class Transform {
public:
	glm::mat4 getTransform();
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 pos);

	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle);
	void setAngle(float angle);
	void addAngle(float angle);

	void setScale(float x, float y, float z);
	void setScale(float s);
	void setScale(glm::vec3 scale);
	void multiplyScale(float x, float y, float z);
	void multiplyScale(glm::vec3 scale);
	glm::vec3 getScale();

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotateAxis = glm::vec3(1, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	float angle = 0.0f;
};


