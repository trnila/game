#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "../Utils/Observer.h"
#include "../Window.h"
#include "Node.h"

class Camera : public Subject<Camera>, public Observer<Window>, public Node {
public:
	Camera(Window &window);
	~Camera();

	void render(RenderContext &context) override;
	Object *find(int id) override;

	const glm::mat4 getLookAt();
	glm::mat4 getPerspective() const;

	void rotateBy(double vert, double hor);
	void setRotation(float vert, float hor);

	void setZFar(float zFar);
	void setZNear(float zNear);

	void forward(float diff);

	void backward(float diff);

	void left(float diff);

	void right(float diff);

	virtual void updated(Window &camera) override;

	glm::vec3 getDirection();

protected:
	void transformed() override;

private:
	Window &window;

	glm::vec3 up;
	glm::vec3 target;

	float v, h;
	int width, height;
	float zFar, zNear;
};
