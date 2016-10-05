#include "Scene.h"

Scene::Scene(GLFWwindow *window) : camHandler(&camera) {
	init_resources();

	objects.emplace_back(Object(new Model("resources/cylinder.obj"), prog));
	objects.emplace_back(Object(new Model("resources/torus.obj"), prog));
	objects.emplace_back(Object(new Model("resources/monkey.obj"), prog));
	objects.emplace_back(Object(new Model("resources/terrain.obj"), prog));
	/*
	objects.emplace_back(Object(new Model(triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(new Model(cubeVertices, cubeRandColors, 36), prog));
	objects.emplace_back(Object(new Model(triangleVertices, triangleBlue, 3), prog));
	objects.emplace_back(Object(new Model("resources/cylinder.obj"), prog));
	 */

	objects[0].setPosition(-1, 0, -4);
	objects[0].rotate(0, 0, 1, 0);
	objects[0].setScale(5, 5, 1);

	objects[1].setPosition(0, 0, -9);
	objects[1].rotate(0, 1, -1, 1);

	objects[2].setPosition(2, 0, -3);
	objects[2].rotate(0, 0, 1, 0);

	objects[3].setPosition(-1, -10, -4);
	objects[3].rotate(0, 0, 1, 0);
	objects[3].setScale(5, 5, 5);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera.setViewportSize(width, height);

	camera.setPosition(0, 0, 1.004475f);
	camera.setRotation(-0.091711f, -3.180683f);
}

int Scene::init_resources() {
	try {
		Shader vertex = ResourceManager<Shader>::getInstance().getResource<>("triangle.v.glsl", GL_VERTEX_SHADER);
		Shader fragment = ResourceManager<Shader>::getInstance().getResource<>("triangle.f.glsl", GL_FRAGMENT_SHADER);

		prog.attach(vertex);
		prog.attach(fragment);
		prog.link();

		camera.addListener(&prog);

	} catch(GlslCompileError &err) {
		std::cerr << "GLSL error: " << err.getSource() << " - " << err.what() << "\n";
	}

	return 1;
}

void Scene::update(float time) {
	float angle = time * 45;

	for(Object &o: objects) {
		o.addAngle(angle);
	}
	objects[1].move(0, 0, time);
	objects[0].setScale(scale, scale, scale);

	scale += 2 * scaleSign * time;

	if (scale <= 0.1) {
		scaleSign = 1;
	} else if (scale >= 5.0) {
		scaleSign = -1;
	}

	camHandler.update(time);
}

void Scene::renderOneFrame(RenderContext &context) {
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.setCamera(&camera);

	for(Object &o: objects) {
		o.render(context);
	}
}

void Scene::onKey(int key, int scancode, int action, int mods) {
	camHandler.onKey(key, scancode, action, mods);
}

void Scene::onMove(GLFWwindow *window, double x, double y) {
	camHandler.onMove(window, x, y);
}

