#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Scene.h"
#include "Singleton.h"
#include "KeyListener.h"
#include "MouseListener.h"

class Game : public Singleton<Game>, KeyListener, MouseListener {
public:
	void init();
	void start();

private:
	virtual void onKey(int key, int scancode, int action, int mods) override;

	virtual void onMove(GLFWwindow *window, double x, double y) override;

private:
	GLFWwindow* window;
	Scene *scene;
};
