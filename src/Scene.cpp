#include <glm/ext.hpp>
#include "Scene.h"
#include "data.h"
#include "Scene/Light.h"
#include "States.h"
#include "State.h"


Scene::Scene(Window &window) : camera(window), camHandler(&camera), window(window) {
	initResources();
	createScene();
}

void Scene::createScene() {
	Object *obj;
	//Object *terrain = factory->create("resources/terrain_smooth.obj");
//	terrain = factory->create("resources/plane.obj");

	/*terrain->setPosition(-7, -3, -2);
	terrain->rotate(0, 0, 0, 1);
	terrain->setScale(10, 10, 10);
	terrain->setColor(0, 123 / 255.0f, 10 / 255.0f);

	root.addNode(terrain);*/

	/*NodeList *windMill = new NodeList();
	windMill->move(0, 0.5, 0);

	NodeList *propeller = new NodeList();
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

	obj = factory->create("resources/ball.obj");
	obj->setScale(0.02, 0.02, 0.02);
	obj->setColor(1, 1, 1);
	propeller->addNode(obj);

	for (int i = 0; i < 4; i++) {
		obj = new Object(-1, new Model("redTriangle", triangleVertices, 3), prog, shadow, nullptr);
		obj->rotate(90 * i, 0.6, 0, 1);
		obj->setScale(1, 1, 1);
		obj->setColor(colors[i]);
		propeller->addNode(obj);
	}
	// tube
	obj = factory->create("resources/tube.obj");
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.05, 1, 0.05);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	windMill->addNode(obj);
	windMill->addNode(propeller);

	root.addNode(windMill);*/


	NodeList *forest = new NodeList();
	forest->move(17.65, -3.0, 26.88);
	root.addNode(forest);

	obj = factory->create("resources/tree.obj");
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
	forest->addNode(obj);

	obj = factory->create("resources/tree.obj");
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

	/*obj = new Object(-1, new Model("redTriangle", triangleVertices, 3), prog, shadow, nullptr);
	obj->move(-0.1, -1, 0);
	obj->setColor(1, 0, 0);
	origin->addNode(obj);*/


	/*lightContainer = new NodeList();
	lightContainer->setPosition(15.514797f, 2.126692f, 0.289154f);
	lightContainer->rotate(0, 0, 1, 0);
	lightContainer->attachLogic<RotateLogic>(45);
	root.addNode(lightContainer);

	lightNode = new Light(prog);
	lightNode->setPosition(10, 10, 10);
	lightNode->setDiffuseColor(Color(1, 1, 1));
	lightNode->setSpecularColor(Color(0, 0, 1));
	lightNode->setDirection(glm::vec3(15.514797f, 2.126692f, 0.289154f));
	lightContainer->addNode(lightNode);
	//root.addNode(lightNode);*/

	/*obj = factory->create("resources/ball.obj");
	obj->move(12, 10, 10);
	obj->setColor(1, 0, 0);
	lightContainer->addNode(obj);*/


	NodeList* cubes = new NodeList();
	cubes->move(10.7, 0.78, 8.81);
	root.addNode(cubes);
	obj = factory->create("resources/cube.obj");
	obj->setPosition(0, 0, 0);
	obj->setColor(1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = factory->create("resources/cube.obj");
	obj->setPosition(-2, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, -1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = factory->create("resources/monkey.obj");
	obj->setPosition(13, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, -1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = factory->create("resources/monkey_smooth.obj");
	obj->setPosition(10, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, 1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = factory->create("resources/Vortigaunt/vortigaunt.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(15, 0, 5);
	obj->setScale(1.f);
	obj->setScale(0.01);
	root.addNode(obj);

	obj = factory->create("resources/D0G/a.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(16, 0, 5);
	obj->setScale(1.f);
	root.addNode(obj);

	obj = factory->create("resources/Headcrab classic/headcrabclassic.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(18, 0, 5);
	obj->setScale(0.05f);
	root.addNode(obj);

	NodeList *ro = new NodeList();
	ro->rotate(0, 0, 1, 0);
	ro->attachLogic<RotateLogic>(20);
	root.addNode(ro);

	NodeList *e1 = new NodeList();
	e1->rotate(0, 0, 1, 0);
	ro->addNode(e1);

	NodeList *e2 = new NodeList();
	e2->rotate(0, 0, 1, 0);
	e2->setPosition(100, 0, 0);
	e1->addNode(e2);

	obj = factory->create("resources/earth/earth.obj");
	obj->setColor(1, 1, 1);
	obj->setScale(0.05f);
	e2->addNode(obj);

	NodeList *m = new NodeList();
	m->rotate(0, 0, 1, 0);
	m->attachLogic<RotateLogic>(-90);
	e2->addNode(m);

	obj = factory->create("resources/moon/moon.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(20, 0, 0);
	obj->setScale(0.05f);
	m->addNode(obj);

	/*obj = factory->create("resources/earth/earth.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(100, 0, 0);
	obj->setScale(0.05f);
	obj->attachLogic<RotateLogic>(15);
	ro->addNode(obj);*/



	obj = factory->create("resources/Strider/Strider.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(18, -5, 30);
	obj->setScale(0.02f);
	root.addNode(obj);

	//obj = factory->create("resources/Strider/Strider.obj");
	//obj = factory->create("resources/Gman/gman.obj");
	//obj = factory->create("resources/AntLion/AntLion.obj");
	NodeList *center = new NodeList();
	center->setPosition(18, 0, 5);
	root.addNode(center);

	obj = factory->create("resources/Combine Scanner/Combine_Scanner.obj");
	obj->setColor(1, 1, 1);
	obj->setScale(0.01f);
	center->addNode(obj);

	Light *light = new Light(prog, 6, LightType::SpotLight);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setConeAngle(15);
	center->addNode(light);
	center->attachLogic<FollowLogic>(&camera, light);


	NodeList *balls = new NodeList();
	balls->move(15, 0, 0);
	root.addNode(balls);

	float coords[][3] = {
			{0, 0, -1},
			{1, 0, 0},
			{0, 0, 1},
			{-1, 0, 0}
	};
	int modif = 2;
	for(int i = 0; i < 4; i++) {
		obj = factory->create("resources/ball.obj");
		obj->setPosition(modif * coords[i][0], modif * coords[i][1], modif * coords[i][2]);
		balls->addNode(obj);
	}


	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);
	camera.setZFar(20000);

	prog.setAmbientColor(ambientColor);

	skybox = new Skybox();


	camera.addListener(&skybox->program);

	light = new Light(prog, 0, LightType::Directional);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setDirection(glm::vec3(-0.550664, -0.395870, 0.734885));
	root.addNode(light);
	
/*	light = new Light(prog, 1, LightType::Point);
	light->setDiffuseColor(Color(1, 0, 0));
	light->setSpecularColor(Color(1, 0, 0));
	light->setDirection(glm::vec3(15.514797f, 2.126692f, 0.289154f));
	root.addNode(light);


	NodeList *node = new NodeList();
	node->rotate(0, 0, 1, 0);
	node->attachLogic<RotateLogic>(45);

/*	obj = factory->create("resources/ball.obj");
	obj->setPosition(15, 15, 0);
	node->addNode(obj);*/

	/*light = new Light(prog, 2, LightType::Point);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setDirection(glm::vec3(0, 1, 1));
	light->setPosition(15, 15, 0);
	node->addNode(light);
	root.addNode(node);*/
	terrain = new Terrain();
	terrain->getTransform().setPosition(0, -5, -30);
	terrain->getTransform().setScale(5, 1, 5);
}

void Scene::initResources() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	camera.addListener(&prog);

	factory = new ObjectFactory(prog, shadowRenderer.program);
	states.add(StateType::Insert, new Insert(), GLFW_KEY_I);
	states.add(StateType::Delete, new Delete(), GLFW_KEY_X);
	states.add(StateType::Scale, new Scale(), GLFW_KEY_S);
	states.add(StateType::Lights, new Lights(), GLFW_KEY_L);
	states.add(StateType::Shoot, new Shoot(), GLFW_KEY_SPACE);
	states.change(StateType::Normal);
}

void Scene::update(float time) {
	glm::mat4 parent(1.0f);
	root.update(time, parent);
	camHandler.update(time);
}

void Scene::renderOneFrame(RenderContext &context) {
	glm::mat4 depthMVP;
	Texture& shadowTexture = shadowRenderer.render(context, root, depthMVP);

	context.setStage(RenderStage::Normal);
	window.setViewport();
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->render(context);
	terrain->draw(*this);

	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	prog.send("depthBias", depthBiasMVP);

	prog.useTexture("shadowTexture", shadowTexture, 1);
	root.render(context);
}

void Scene::onKey(int key, int scancode, int action, int mods) {
	camHandler.onKey(key, scancode, action, mods);
	states.current().onKey(key, scancode, action, mods, *this);
}

void Scene::onMove(double x, double y) {
	camHandler.onMove(x, y);
}

void Scene::onClick(int button, int action, double x, double y) {
	if (action != GLFW_PRESS) {
		return;
	}

	int newY = window.getHeight() - y;
	float depth;

	//glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	int index;
	glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	Object* o = root.find(index);

	glm::vec3 screenX = glm::vec3(x, newY, depth);
	glm::mat4 view = camera.getTransform();
	glm::mat4 projection = camera.getPerspective();

	glm::vec4 viewPort = glm::vec4(0, 0, window.getWidth(), window.getHeight());
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	states.current().onClick(pos, o, *this);
}

