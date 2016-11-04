#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Observer.h"

class Window : public Subject<Window> {
public:
	Window(int width, int height, const char *title);
	~Window();
	bool shouldClose() const;
	void swapBuffers() const;

	int getWidth();
	int getHeight();

	void setViewport();

private:
	GLFWwindow *window;
	int width, height;
};


