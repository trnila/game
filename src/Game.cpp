#include "Game.h"
#include "Groups.h"
#include "Scene/Lights/DirectionalLight.h"
#include "State.h"

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
	
	states = new States(this);
	states->add(StateType::Insert, new Insert(), GLFW_KEY_I);
	states->add(StateType::Delete, new Delete(), GLFW_KEY_X);
	states->add(StateType::Scale, new Scale(), GLFW_KEY_S);
	states->add(StateType::Lights, new Lights(), GLFW_KEY_L);
	states->add(StateType::Shoot, new Shoot(), GLFW_KEY_SPACE);
	states->change(StateType::Normal);
	addKeyboard(states);
	addMouse(states);

	Factory* factory = new Factory();
	factory->add({
			CameraFactory(this),
			SkyboxFactory("resources/skyboxes/ely_hills/hills"),
			normal_terrain,
			//Forest(),
			//TwoCubes(),
			VariousObjects(),
			Earth(),
			//Balls(),
			//RotatingSpotLight(),
			CombineScanner(),
			[](Scene* scene) -> void {
				NodeList* root = scene->getRootNode().createGroup();
				root->setPosition(188.013016, 33.348019, 207.685776);

				root->createEntity("resources/Gman/gman.obj")->setScale(0.02);
				root->createEntity("resources/normals/plane.obj")->setPosition(1.5, 0, 0);
				root->createEntity("resources/normals/without.obj")->setPosition(-1.5, 0, 0);
			},
			create_water,
			[](Scene* scene) -> void {
				DirectionalLight *light = scene->getRootNode().createLight<DirectionalLight>(0);
				light->setDiffuseColor(Color(1, 1, 1));
				light->setSpecularColor(Color(1, 1, 1));
				light->setDir(glm::vec3(-0.550664, -0.395870, 0.734885));

				DirectionalLight *spot = scene->getRootNode().createLight<DirectionalLight>(5);
				spot->setDiffuseColor(Color(1, 1, 1));
				spot->setSpecularColor(Color(1, 1, 1));
				spot->setPosition(200.581467, 33.916870+20, 216.247879);
				spot->setDir(glm::vec3(0.673366, -0.393158, -0.626103));
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
}

void Game::onMove(double x, double y) {
	for(auto i: mouse) {
		i->onMove(x, y);
	}
}

Window &Game::getWindow() {
	return *window;
}

States *Game::getStates() {
	return states;
}

Scene *Game::getScene() {
	return scene;
}

void Game::onClick(int button, int action, double x, double y) {
	if (action != GLFW_PRESS) {
		return;
	}

	int newY = window->getHeight() - y;
	float depth;

	glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	int index;
	glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	glm::vec3 screenX = glm::vec3(x, newY, depth);
	glm::mat4 view = scene->getActiveCamera().getLookAt();
	glm::mat4 projection = scene->getActiveCamera().getPerspective();

	glm::vec4 viewPort = glm::vec4(0, 0, window->getWidth(), window->getHeight());
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	states->current().onClick(pos, scene->getRootNode().find(index), *scene);
	printf("glm::vec3{%f, %f, %f},\n", pos.x, pos.y, pos.z);
}
