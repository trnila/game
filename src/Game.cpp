#include "Game.h"
#include "Factory.h"
#include "Groups.h"
#include "Scene/Lights/DirectionalLight.h"

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


	Factory* factory = new Factory();
	factory->add({
			CameraFactory(this),
			SkyboxFactory("resources/skyboxes/ely_hills/hills"),
			normal_terrain,
			Forest(),
			TwoCubes(),
			VariousObjects(),
			Earth(),
			Balls(),
			RotatingSpotLight(),
			CombineScanner(),
			create_water,
			[](Scene* scene) -> void {
				DirectionalLight *light = scene->getRootNode().createLight<DirectionalLight>(0);
				light->setDiffuseColor(Color(1, 1, 1));
				light->setSpecularColor(Color(1, 1, 1));
				light->setDir(glm::vec3(-0.550664, -0.395870, 0.734885));

				DirectionalLight *spot = scene->getRootNode().createLight<DirectionalLight>(5);
				spot->setDiffuseColor(Color(1, 1, 1));
				spot->setSpecularColor(Color(1, 1, 1));
			}
	});

	scene = new Scene(factory);
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

Window &Game::getWindow() {
	return *window;
}
