#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Program.h"
#include "Object.h"
#include "ResourceManager.h"
#include <GLFW/glfw3.h>

class Scene {
public:
	Scene(GLFWwindow *window);
	int init_resources();
	void update(float time);
	void renderOneFrame();

private:
	Program prog;
	glm::mat4 view;
	glm::mat4 projection;
	UniformVariable *mvpVar;

	std::vector<Object> objects;
};
