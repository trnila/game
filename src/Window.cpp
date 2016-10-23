#include <stdexcept>
#include "Window.h"
#include "Game.h"

Window::Window(int width, int height, const char *title) : width(width), height(height) {
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("could not create window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Game::getInstance().onKey(key, scancode, action, mods);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
		Game::getInstance().onMove(x, y);
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) -> void {
		GL_CHECK(glViewport(0, 0, w, h));
		Window *win = (Window *) glfwGetWindowUserPointer(window);
		win->width = w;
		win->height = h;
		win->notify();
	});
}

bool Window::shouldClose() const {
	return (bool) glfwWindowShouldClose(window);
}

void Window::swapBuffers() const {
	glfwSwapBuffers(window);

}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

void Window::setViewport() {
	GL_CHECK(glViewport(0, 0, width, height));

}
