#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera {
public:
	void setDimension(int width, int height);
	const glm::mat4 getTransform();
	void rotateBy(double vert, double hor);
	void move(float x, float y, float z);

	void setPosition(float x, float y, float z);

	void setRotation(float vert, float hor);

private:
	glm::mat4 projection;
	glm::vec3 position;

	float v, h;
};
