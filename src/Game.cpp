#include "Game.h"

void Game::init() {
	glfwSetErrorCallback([] (int err, const char* description) -> void {
		throw std::runtime_error(description);
	});

	if (!glfwInit()) {
		throw std::runtime_error("failed to init glfw");
	}

	window = new Window(800, 600, "The Game");


	GLenum err = glewInit();
	if (err != GLEW_OK) {
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3) {
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glEnable(GL_STENCIL_TEST));
	GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));


	Camera *camera = new Camera(*window);
	CameraHandler* handler = new CameraHandler(camera);
	camera->attachLogic([=](Node& node, float df, Scene& root) -> void {
		handler->operator()(node, df, root);
	});
	keyboard.push_back(handler);
	mouse.push_back(handler);
	scene = new Scene(camera);
}

void Game::startRendering() {
	RenderContext context(*window);

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
	for(auto i: keyboard) {
		i->onKey(key, scancode, action, mods);
	}
//	scene->getStates().current().onKey(key, scancode, action, mods, *this); //TODO: fix
}

void Game::onMove(double x, double y) {
	for(auto i: mouse) {
		i->onMove(x, y);
	}
}
