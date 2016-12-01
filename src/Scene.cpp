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
#include "Groups.h"
#include "Panel.h"

Scene::Scene(Window &window) : camera(window), camHandler(&camera), window(window) {
	initResources();
	createScene();
	panel = new Panel();
}

void Scene::createScene() {
	createTerrain();
	createObjects();
	createSkybox();

	//camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	//camera.setRotation(-0.582351f, -0.1290f);
	camera.setZFar(20000);
	camera.setPosition(188.013016f, 100 + 33.348019f, 208.685776f);
	camera.attachLogic(CamInit());
	getRootNode().addNode(&camera);
	getRootNode().getMediator().setAmbientLight(Color(0.1, 0.1, 0.1));

	DirectionalLight *light = root->createLight<DirectionalLight>(0);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setDir(glm::vec3(-0.550664, -0.395870, 0.734885));
	root->addNode(light);

	/*for(int i = 0; i < 10; i++) {
		BaseLight *l = root->getLight(i);
		if(l) {
			l->setActive(false);
		}
	}*/

	DirectionalLight *spot = root->createLight<DirectionalLight>(5);
	spot->setDiffuseColor(Color(1, 1, 1));
	spot->setSpecularColor(Color(1, 1, 1));
}

void Scene::createSkybox() {//skybox = new Skybox("resources/skyboxes/ame_nebula/purplenebula");
	skybox = new Skybox("resources/skyboxes/ely_hills/hills");
	camera.addListener(&skybox->program);
}

Camera *scan;
void Scene::createObjects() {
	std::vector<std::function<void(Scene*)>> groups {
			Forest(),
	        TwoCubes(),
	        VariousObjects(),
	        Earth(),
	        Balls(),
	        RotatingSpotLight(),
	        //CombineScanner()
	};

	NodeList *center = this->getRootNode().createGroup();
	center->setPosition(18, 0, 5);

	Object *obj = center->createEntity("resources/Combine Scanner/Combine_Scanner.obj");
	obj->setColor(1, 1, 1);
	obj->setScale(0.01f);

	SpotLight *light = center->createLight<SpotLight>(6);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setConeAngle(15);
	center->attachLogic(FollowLogic(&this->getActiveCamera(), light));

	scan = new Camera(window);
	center->addNode(scan);

	for(auto group: groups) {
		group(this);
	}
}

void Scene::createTerrain() {
	terrain = new Terrain(root->getMediator());
	terrain = new GeneratedTerrain(root->getMediator());
	terrain->init();
	terrain->getTransform().setScale(5, 90, 5);


	water.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	water.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/water.f.glsl", GL_FRAGMENT_SHADER));
	water.link();
	camera.addListener(&water);

	ResourceManager<Model> &models = ResourceManager<Model>::getInstance();
	Object *obj = new Object(0, &models.getResource("resources/brickwall.obj"), water, water, nullptr);
	obj->setScale(1000);
	obj->setPosition(100, -150, 0);
	root->addNode(obj);
}

void Scene::initResources() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	Mediator* mediator = new Mediator(new ObjectFactory(prog, shadowRenderer.program));
	root = new NodeList(*mediator);
	mediator->registerProgram(&prog);
	mediator->setScene(this);

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
}

void Scene::renderOneFrame(RenderContext &context) {
	glm::mat4 depthMVP;
	Texture& shadowTexture = shadowRenderer.render(context, this, depthMVP);

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

	panel->texture = &shadowTexture;
	panel->render();

//	GL_CHECK(glViewport(0, 0, 800, 600));
//	root->render(context);
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
	glm::mat4 view = camera.getLookAt();
	glm::mat4 projection = camera.getPerspective();

	glm::vec4 viewPort = glm::vec4(0, 0, window.getWidth(), window.getHeight());
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	printf("%f, %f, %f\n", pos.x, pos.y, pos.z);
	states.current().onClick(pos, o, *this);
}

Terrain *Scene::getTerrain() const {
	return terrain;
}

