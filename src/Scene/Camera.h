#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "../Utils/Observer.h"
#include "../Window.h"

class Camera : public Subject<Camera>, public Observer<Window> {
public:
	Camera(Window &window);
	~Camera();

	const glm::mat4 getTransform();
	void rotateBy(double vert, double hor);
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setRotation(float vert, float hor);
	glm::vec3 getPosition() {
		return position;
	}

	void setZFar(float zFar);

	void setZNear(float zNear);
	glm::mat4 getPerspective() const;

	void forward(float diff);

	void backward(float diff);

	void left(float diff);

	void right(float diff);

	virtual void updated(Window &camera) override;

	const glm::vec3 &getDirection();

private:
	Window &window;

	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 target;

	float v, h;
	int width, height;
	float zFar, zNear;
};
