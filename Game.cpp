#include "Game.h"

void Game::init() {
	glfwSetErrorCallback([] (int err, const char* description) -> void {
		throw std::runtime_error(description);
	});

	if (!glfwInit()) {
		throw std::runtime_error("failed to init glfw");
	}
	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("could not create window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Game::getInstance().onKey(key, scancode, action, mods);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		float horChange = float(width / 2 - x);
		float vertChange = float(height / 2 - y);
		glfwSetCursorPos(window, width / 2, height / 2);

		Game::getInstance().onMove(horChange, vertChange);
	});
	glfwSetWindowSizeCallback(window, [] (GLFWwindow* window, int width, int height) -> void {
		glViewport(0, 0, width, height);
	});


	GLenum err = glewInit();
	if (err != GLEW_OK) {
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3) {
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	glEnable(GL_DEPTH_TEST);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
	glViewport(0, 0, width, height);

	scene = new Scene(window);
}

void Game::start() {
	RenderContext context;

	double last = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double current = glfwGetTime();
		float delta = (float) (current - last);
		last = current;

		scene->update(delta);
		scene->renderOneFrame(context);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::onKey(int key, int scancode, int action, int mods) {
	scene->onKey(key, scancode, action, mods);
}

void Game::onMove(double x, double y) {
	scene->onMove(x, y);
}
