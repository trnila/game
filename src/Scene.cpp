#include "Scene.h"
#include "data.h"
#include "Logic.h"
#include "Light.h"

Scene::Scene(Window &window) : camera(window), camHandler(&camera) {
	initResources();

	createScene();
}

Node* obj1, *obj2;

void Scene::createScene() {
	ResourceManager<Model> &resources = ResourceManager<Model>::getInstance();

	Object *obj;
	Object *terrain = new Object(&resources.getResource("resources/terrain.obj"), prog, nullptr);

	terrain->setPosition(0, 0, 0);
	terrain->rotate(0, 0, 0, 1);
	terrain->setScale(2, 3, 2);
	terrain->setColor(0, 123 / 255.0f, 10 / 255.0f);

	root.addNode(terrain);

	glm::vec3 center = glm::vec3(0.2787f, 1.811f, -0.48f);

	windMill = new NodeList();
	windMill->move(0, 0.5, 0);

	propeller = new NodeList();
	propeller->move(0, 1, -0.05f);
	propeller->rotate(0, 0.6, 0, 1);
	propeller->attachLogic<RotateLogic>(45);
	// propellers
	glm::vec3 colors[] = {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{1, 1, 0}
	};

	obj = new Object(&resources.getResource("resources/ball.obj"), prog, nullptr);
	obj->setScale(0.02, 0.02, 0.02);
	obj->setColor(1, 1, 1);
	propeller->addNode(obj);

	for (int i = 0; i < 4; i++) {
		obj = new Object(&resources.getResource("redTriangle", triangleVertices, 3), prog, nullptr);
		obj->rotate(90 * i, 0.6, 0, 1);
		obj->setScale(1, 1, 1);
		obj->setColor(colors[i]);
		propeller->addNode(obj);
	}
	// tube
	obj = new Object(&resources.getResource("resources/tube.obj"), prog, nullptr);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.05, 1, 0.05);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	windMill->addNode(obj);
	windMill->addNode(propeller);

	root.addNode(windMill);


	NodeList *forest = new NodeList();
	forest->move(3, 0.1, 5.68);
	root.addNode(forest);

	obj = new Object(&resources.getResource("resources/tree.obj"), prog, nullptr);
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
	forest->addNode(obj);

	obj = new Object(&resources.getResource("resources/tree.obj"), prog, nullptr);
	obj->setPosition(0, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.04, 0.2, 9);
	forest->addNode(obj);


	NodeList *origin = new NodeList;
	root.addNode(origin);
	origin->setPosition(1, 2, 1);
	origin->rotate(90, 0, 0, 1);
	origin->attachLogic<RotateLogic>(45);

	obj = new Object(&resources.getResource("redTriangle", triangleVertices, 3), prog, nullptr);
	obj->move(-0.1, -1, 0);
	obj->setColor(1, 0, 0);
	origin->addNode(obj);


	glm::vec3 pos(-0.280287, 6.302092, -4.222088);
	Light *light = new Light(prog);
	light->setPosition(pos);
	//light->attachLogic<MoveLogic>();
	root.addNode(light);
	obj1 = light;

	obj = new Object(&resources.getResource("resources/ball.obj"), prog, nullptr);
	obj->setScale(0.02, 0.02, 0.02);
	obj->setPosition(pos);
	//obj->attachLogic<MoveLogic>();
	root.addNode(obj);

	obj2 = obj;

	obj = new Object(&resources.getResource("resources/cube.obj"), prog, new Texture("resources/cube.png"));
	obj->setPosition(7, 0, 0);
	obj->setColor(1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = new Object(&resources.getResource("resources/cube.obj"), prog, new Texture("resources/cube_wood.png"));
	obj->setPosition(7, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, -1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);


	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);
}

void Scene::initResources() {
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

	if(key == GLFW_KEY_SPACE) {
		obj1->setPosition(camera.getPosition());
		//obj2->setPosition(camera.getPosition());
	}
}

void Scene::onMove(double x, double y) {
	camHandler.onMove(x, y);
}

