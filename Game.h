#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Scene.h"

class Game {
public:
	void init();
	void start();

private:
	GLFWwindow* window;
	Scene *scene;
};
