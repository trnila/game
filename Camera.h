#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Observer.h"
#include "Window.h"

class Camera : public Subject<Camera>, public Observer<Window> {
public:
	Camera(Window &window);

	~Camera();

	void setViewportSize(int width, int height);
	const glm::mat4 getTransform();
	void rotateBy(double vert, double hor);
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setRotation(float vert, float hor);

	void setZFar(float zFar);

	void setZNear(float zNear);
	glm::mat4 getPerspective() const;

	virtual void updated(Window &camera) override;

private:
	glm::vec3 position;
	Window &window;

	float v, h;
	int width, height;
	float zFar, zNear;
};
