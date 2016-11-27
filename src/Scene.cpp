#include <glm/ext.hpp>
#include "Scene.h"
#include "data.h"
#include "Scene/Lights/BaseLight.h"
#include "States.h"
#include "State.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Scene/Lights/PointLight.h"
#include "Scene/Lights/SpotLight.h"
#include "GeneratedTerrain.h"

Scene::Scene(Window &window) : camera(window), camHandler(&camera), window(window) {
	initResources();
	createScene();
}

void Scene::createScene() {
	createTerrain();
	createForest();
	create2Cubes();
	createVariousObjects();
	createEarth();
	createBalls();
	createRotatingSpotLight();
	createScanner();


	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);
	camera.setZFar(20000);

	prog.setAmbientColor(ambientColor);

	//skybox = new Skybox("resources/skyboxes/ame_nebula/purplenebula");
	skybox = new Skybox("resources/skyboxes/ely_hills/hills");


	camera.addListener(&skybox->program);

	DirectionalLight *light = root->createLight<DirectionalLight>(0);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setDirection(glm::vec3(-0.550664, -0.395870, 0.734885));
	root->addNode(light);
}

void Scene::createTerrain() {
	terrain = new Terrain(root->getMediator());
	//terrain = new GeneratedTerrain();
	terrain->init();
	terrain->getTransform().setPosition(0, -5, -30);
	terrain->getTransform().setScale(5, 1, 5);
}

void Scene::createEarth() {
	NodeList *ro = root->createGroup();
	ro->rotate(0, 0, 1, 0);
	ro->attachLogic<RotateLogic>(20);

	NodeList *e1 = ro->createGroup();
	e1->rotate(0, 0, 1, 0);

	NodeList *e2 = e1->createGroup();
	e2->rotate(0, 0, 1, 0);
	e2->setPosition(100, 0, 0);

	Object *obj = e2->createEntity("resources/earth/earth.obj");
	obj->setColor(1, 1, 1);
	obj->setScale(0.05f);

	NodeList *m = e2->createGroup();
	m->rotate(0, 0, 1, 0);
	m->attachLogic<RotateLogic>(-90);

	obj = m->createEntity("resources/moon/moon.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(20, 0, 0);
	obj->setScale(0.05f);
}

void Scene::createVariousObjects() {
	Object *obj = root->createEntity("resources/monkey.obj");
	obj->setPosition(13, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, -1, 0);
	obj->attachLogic<RotateLogic>(40);

	obj = root->createEntity("resources/monkey_smooth.obj");
	obj->setPosition(10, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, 1, 0);
	obj->attachLogic<RotateLogic>(40);

	obj = root->createEntity("resources/Vortigaunt/vortigaunt.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(15, 0, 5);
	obj->setScale(1.f);
	obj->setScale(0.01);

	obj = root->createEntity("resources/D0G/a.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(16, 0, 5);
	obj->setScale(1.f);

	obj = root->createEntity("resources/Headcrab classic/headcrabclassic.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(18, 0, 5);
	obj->setScale(0.05f);

	obj = root->createEntity("resources/Strider/Strider.obj");
	obj->setColor(1, 1, 1);
	obj->setPosition(18, -5, 30);
	obj->setScale(0.02f);


	//obj = factory->create("resources/Strider/Strider.obj");
	//obj = factory->create("resources/Gman/gman.obj");
	//obj = factory->create("resources/AntLion/AntLion.obj");
}

void Scene::create2Cubes() {
	NodeList* cubes = root->createGroup();
	cubes->move(10.7, 0.78, 8.81);

	Object *obj = cubes->createEntity("resources/cube.obj");
	obj->setPosition(0, 0, 0);
	obj->setColor(1, 0, 0);
	obj->attachLogic<RotateLogic>(40);

	obj = cubes->createEntity("resources/cube.obj");
	obj->setPosition(-2, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, -1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
}

void Scene::createForest() {
	NodeList *forest = root->createGroup();
	forest->move(17.65, -3.0, 26.88);

	Object *obj = forest->createEntity("resources/tree.obj");
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);

	obj = forest->createEntity("resources/tree.obj");
	obj->setPosition(0, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.04, 0.2, 9);
}

void Scene::createBalls() {
	NodeList *balls = root->createGroup();
	balls->move(15, 0, 0);

	float coords[][3] = {
			{0, 0, -1},
			{1, 0, 0},
			{0, 0, 1},
			{-1, 0, 0}
	};
	int modif = 2;
	for(int i = 0; i < 4; i++) {
		Object *obj = balls->createEntity("resources/ball.obj");
		obj->setPosition(modif * coords[i][0], modif * coords[i][1], modif * coords[i][2]);
	}

	BaseLight *light = balls->createLight<PointLight>(1);
	light->setDiffuseColor(Color(1, 0, 0));
	light->setSpecularColor(Color(1, 0, 0));
	light->setPosition(glm::vec3(0, 1, 0));
	balls->addNode(light);
}

void Scene::initResources() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	Mediator* mediator = new Mediator(new ObjectFactory(prog, shadowRenderer.program));
	root = new NodeList(*mediator);
	mediator->registerProgram(&prog);

	camera.addListener(&prog);
	states.add(StateType::Insert, new Insert(), GLFW_KEY_I);
	states.add(StateType::Delete, new Delete(), GLFW_KEY_X);
	states.add(StateType::Scale, new Scale(), GLFW_KEY_S);
	states.add(StateType::Lights, new Lights(), GLFW_KEY_L);
	states.add(StateType::Shoot, new Shoot(), GLFW_KEY_SPACE);
	states.change(StateType::Normal);
}

void Scene::update(float time) {
	glm::mat4 parent(1.0f);
	root->update(time, parent);
	camHandler.update(time);

	auto pos = camera.getPosition();



	camera.setPosition(pos.x, terrain->getHeightAt(pos.x, pos.z), pos.z);
}

void Scene::renderOneFrame(RenderContext &context) {
	glm::mat4 depthMVP;
	Texture& shadowTexture = shadowRenderer.render(context, *root, depthMVP);

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
	root->render(context);
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

	Object* o = root->find(index);

	glm::vec3 screenX = glm::vec3(x, newY, depth);
	glm::mat4 view = camera.getTransform();
	glm::mat4 projection = camera.getPerspective();

	glm::vec4 viewPort = glm::vec4(0, 0, window.getWidth(), window.getHeight());
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	states.current().onClick(pos, o, *this);
}

void Scene::createRotatingSpotLight() {
	NodeList *node = root->createGroup();
	node->setPosition(18.837509, 5.312332, 0.827486);

	NodeList *rot = node->createGroup();
	rot->attachLogic<RotateLogic>(45);
	rot->rotate(0, 0, 1, 0);

	/*obj = factory->create("resources/ball.obj");
	obj->setPosition(5, 0, 0);
	rot->addNode(obj);*/

	SpotLight *light = rot->createLight<SpotLight>(2);
	light->setDiffuseColor(Color(0, 1, 0));
	light->setSpecularColor(Color(0, 1, 0));
	light->setPosition(5, 0, 0);
	light->setDirection(glm::vec3(0, -1, 0));
}

void Scene::createScanner() {
	NodeList *center = root->createGroup();
	center->setPosition(18, 0, 5);

	Object *obj = center->createEntity("resources/Combine Scanner/Combine_Scanner.obj");
	obj->setColor(1, 1, 1);
	obj->setScale(0.01f);

	SpotLight *light = center->createLight<SpotLight>(6);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setConeAngle(15);
	center->attachLogic<FollowLogic>(&camera, light);
}

