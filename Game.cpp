#include "Game.h"

void Game::init() {
	glfwSetErrorCallback([] (int err, const char* description) -> void {
		throw std::runtime_error(description);
	});

	if (!glfwInit()) {
		throw std::runtime_error("failed to init glfw");
	}

	window = new Window(640, 480, "The Game");


	GLenum err = glewInit();
	if (err != GLEW_OK) {
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3) {
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	glEnable(GL_DEPTH_TEST);

	scene = new Scene(*window);
}

void Game::startRendering() {
	RenderContext context;

	double last = glfwGetTime();
	while (!window->shouldClose()) {
		double current = glfwGetTime();
		float delta = (float) (current - last);
		last = current;

		scene->update(delta);
		scene->renderOneFrame(context);

		window->swapBuffers();
		glfwPollEvents();
	}
}

void Game::onKey(int key, int scancode, int action, int mods) {
	scene->onKey(key, scancode, action, mods);
}

void Game::onMove(GLFWwindow *window, double x, double y) {
	scene->onMove(window, x, y);
}
