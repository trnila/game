#include "Scene.h"
#include "data.h"

Scene::Scene(GLFWwindow *window) {
	init_resources();

	objects.emplace_back(Object(new Model(triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(new Model(cubeVertices, cubeRandColors, 36), prog));
	objects.emplace_back(Object(new Model(triangleVertices, triangleBlue, 3), prog));

	objects[0].setPosition(-1, 0, -4);
	objects[0].rotate(0, 0, 1, 0);
	objects[0].setScale(5, 5, 1);

	objects[1].setPosition(0, 0, -9);
	objects[1].rotate(0, 0, -1, 0);

	objects[2].setPosition(2, 0, -3);
	objects[2].rotate(0, 0, 1, 0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera.setDimension(width, height);
}

int Scene::init_resources() {
	try {
		Shader vertex = ResourceManager<Shader>::getInstance().getResource<>("triangle.v.glsl", GL_VERTEX_SHADER);
		Shader fragment = ResourceManager<Shader>::getInstance().getResource<>("triangle.f.glsl", GL_FRAGMENT_SHADER);

		prog.attach(vertex);
		prog.attach(fragment);
		prog.link();

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

	double mouseSpeed = time;
	camera.rotateBy(mouseSpeed * vertChange, mouseSpeed * horChange);
	horChange = vertChange = 0;

	if (forward) {
		camera.move(0, 0, -10 * time);
	} else if (backward) {
		camera.move(0, 0, 10 * time);
	}
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
	forward = backward = false;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_UP) {
			forward = true;
		} else if (key == GLFW_KEY_DOWN) {
			backward = true;
		}
	}
}

void Scene::onMove(GLFWwindow *window, double x, double y) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	horChange = float(width / 2 - x);
	vertChange = float(height / 2 - y);
	glfwSetCursorPos(window, width / 2, height / 2);
}
