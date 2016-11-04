#pragma once

#include <glm/mat4x4.hpp>

class Transformable {
public:
	void move(float x, float y, float z);
	void move(glm::vec3 pos);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();

	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle);

	void addAngle(float angle);
	float getAngle();

	void setScale(float x, float y, float z);
	void setScale(float s);
	void setScale(glm::vec3 scale);
	void multiplyScale(float x, float y, float z);
	void multiplyScale(glm::vec3 scale);
	glm::vec3 getScale();
	glm::vec3 getDirection() {
		return glm::vec3(0) - glm::vec3(getTransform() * glm::vec4(0, 1, 0, 1));
	}

protected:
	glm::mat4 getTransform();

	virtual void transformed();

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotateAxis = glm::vec3(1, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	float angle = 0.0f;
};


