#include "Scene.h"
#include "data.h"

Scene::Scene(Window &window) : camera(window), camHandler(&camera), deadTime(0) {
	init_resources();

	ResourceManager<Model> &resources = ResourceManager<Model>::getInstance();

	objects.emplace_back(Object(&resources.getResource("redTriangle", triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(&resources.getResource("resources/ball.obj"), prog));
	objects.emplace_back(Object(&resources.getResource("redTriangle", triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(&resources.getResource("redTriangle", triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(&resources.getResource("redTriangle", triangleVertices, triangleRed, 3), prog));
	objects.emplace_back(Object(&resources.getResource("resources/terrain.obj"), prog));
	objects.emplace_back(Object(&resources.getResource("resources/tube.obj"), prog));
	objects.emplace_back(Object(&resources.getResource("resources/tree.obj"), prog));

	glm::vec3 center = glm::vec3(0.2787f, 1.811f, -0.48f);

	objects[0].setPosition(center);
	objects[0].setRotationPoint(center);
	objects[0].rotate(0, 0.6, 0, 1);
	objects[0].setScale(1, 1, 1);
	objects[0].setColor(1, 0, 0);

	objects[1].setPosition(center);
	objects[1].rotate(0, 0, 0, 1);
	objects[1].setScale(0.01, 0.01, 0.01);
	objects[1].setColor(1, 1, 1);

	objects[2].setPosition(center);
	objects[2].setRotationPoint(center);
	objects[2].rotate(90, 0.6, 0, 1);
	objects[2].setScale(1, 1, 1);
	objects[2].setColor(0, 1, 0);

	objects[3].setPosition(center);
	objects[3].setRotationPoint(center);
	objects[3].rotate(180, 0.6, 0, 1);
	objects[3].setScale(1, 1, 1);
	objects[3].setColor(0, 0, 1);

	objects[4].setPosition(center);
	objects[4].setRotationPoint(center);
	objects[4].rotate(270, 0.6, 0, 1);
	objects[4].setScale(1, 1, 1);
	objects[4].setColor(1, 1, 1);

	objects[5].setPosition(0, 0, 0);
	objects[5].rotate(0, 0, 0, 1);
	objects[5].setScale(1, 2, 1);
	objects[5].setColor(0, 123/255.0f, 10/255.0f);

	objects[6].setPosition(0.2759985f, 0.8f, -0.41095f);
	objects[6].rotate(0, 0, 0, 1);
	objects[6].setScale(0.05, 1, 0.05);
	objects[6].setColor(139/255.0f, 69/255.0f, 19/255.0f);

	objects[7].setPosition(3.4071f, 0.0f, 2.8450f);
	objects[7].rotate(0, 0, 0, 1);
	objects[7].setScale(0.001, 0.001, 0.001);
	objects[7].setColor(139/255.0f, 69/255.0f, 19/255.0f);
	objects[7].setRotationPoint(3.4071f, 0.0f, 2.8450f);

	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);
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
	objects[0].addAngle(angle);
	objects[2].addAngle(angle);
	objects[3].addAngle(angle);
	objects[4].addAngle(angle);

	if(objects[7].getScale().x > 0.1) {
		objects[7].rotate(90, 0, 0, 1);
		deadTime += time;

		if(deadTime > 5) {
			objects[7].rotate(0, 0, 0, 1);
			objects[7].setScale(0.001, 0.001, 0.001);
			deadTime = 0;
		}
	} else {
		objects[7].multiplyScale(1.01, 1.01, 1.01);
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

