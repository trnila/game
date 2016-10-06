#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, const char *title);

	bool shouldClose() const;

	void swapBuffers() const;

	int getWidth() {

	}

	int getHeight() {

	}

private:
	GLFWwindow *window;
	int width, height;
};


