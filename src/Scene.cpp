#include "Scene.h"
#include "data.h"
#include "Logic.h"

Scene::Scene(Window &window) : camera(window), camHandler(&camera), deadTime(0) {
	init_resources();

	ResourceManager<Model> &resources = ResourceManager<Model>::getInstance();


	Object *obj;
	Object *terrain = new Object(&resources.getResource("resources/terrain.obj"), prog);

	terrain->setPosition(0, 0, 0);
	terrain->rotate(0, 0, 0, 1);
	terrain->setScale(2, 3, 2);
	terrain->setColor(0, 123 / 255.0f, 10 / 255.0f);

	root.addNode(terrain);

	glm::vec3 center = glm::vec3(0.2787f, 1.811f, -0.48f);
	float anglePerSec = 45;

	windMill = new NodeList();
	windMill->move(0, 0.5, 0);

	NodeList *propeller = new NodeList();
	propeller->move(0, 1, -0.05f);
	// propellers
	glm::vec3 colors[] = {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{1, 1, 0}
	};
	for (int i = 0; i < 4; i++) {
		obj = new Object(&resources.getResource("redTriangle", triangleVertices, triangleRed, 3), prog);
		obj->setRotationPoint(center);
		obj->rotate(90 * i, 0.6, 0, 1);
		obj->setScale(1, 1, 1);
		obj->setColor(colors[i]);
		obj->attachLogic<RotateLogic>(anglePerSec);
		propeller->addNode(obj);
	}
	// tube
	obj = new Object(&resources.getResource("resources/tube.obj"), prog);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.05, 1, 0.05);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	windMill->addNode(obj);
	windMill->addNode(propeller);

	root.addNode(windMill);


	NodeList *forest = new NodeList();
	forest->move(3, 0.1, 5.68);
	root.addNode(forest);

	obj = new Object(&resources.getResource("resources/tree.obj"), prog);
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
	forest->addNode(obj);

	obj = new Object(&resources.getResource("resources/tree.obj"), prog);
	obj->setPosition(0, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.04, 0.2, 9);
	forest->addNode(obj);


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
	glm::mat4 parent(1.0f);

	root.update(time, parent);
	windMill->move(0.5 * time, 0, 0);
	camHandler.update(time);
}

void Scene::renderOneFrame(RenderContext &context) {
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.setCamera(&camera);

	root.render(context);
}

void Scene::onKey(int key, int scancode, int action, int mods) {
	camHandler.onKey(key, scancode, action, mods);
}

void Scene::onMove(double x, double y) {
	camHandler.onMove(x, y);
}

