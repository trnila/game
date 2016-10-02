#pragma once

#include <GLFW/glfw3.h>

class MouseListener {
public:
	virtual void onMove(GLFWwindow *window, double x, double y) = 0;
};