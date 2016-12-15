#include <glm/ext.hpp>
#include "Scene.h"
#include "Scene/Lights/BaseLight.h"
#include "States.h"
#include "State.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Scene/Lights/PointLight.h"
#include "Scene/Lights/SpotLight.h"
#include "GeneratedTerrain.h"
#include "Groups.h"
#include "Panel.h"

Scene::Scene(Camera* camera) : camera(*camera)  {
	initResources();
	createScene();
}

void Scene::createScene() {
	createTerrain();
	createObjects();
	createSkybox();

	camera.setZFar(20000);
	camera.setPosition(188.013016f, 100 + 33.348019f, 208.685776f);
	//camera.attachLogic(CamInit());
	getRootNode().addNode(&camera);
	getRootNode().getMediator().setAmbientLight(Color(0.1, 0.1, 0.1));

	DirectionalLight *light = root->createLight<DirectionalLight>(0);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(1, 1, 1));
	light->setDir(glm::vec3(-0.550664, -0.395870, 0.734885));
	root->addNode(light);

	DirectionalLight *spot = root->createLight<DirectionalLight>(5);
	spot->setDiffuseColor(Color(1, 1, 1));
	spot->setSpecularColor(Color(1, 1, 1));
}

void Scene::createSkybox() {
	skybox = new Skybox("resources/skyboxes/ely_hills/hills");
	camera.addListener(&skybox->program);
}

void Scene::createObjects() {
	std::vector<std::function<void(Scene*)>> groups {
			Forest(),
	        TwoCubes(),
	        VariousObjects(),
	        Earth(),
	        Balls(),
	        RotatingSpotLight(),
	        CombineScanner(),
	        create_water
	};

	for(auto group: groups) {
		group(this);
	}
}

void Scene::createTerrain() {
	//terrain = new Terrain(root->getMediator());
	terrain = new GeneratedTerrain(root->getMediator());
	terrain->init();
	terrain->getTransform().setScale(5, 90, 5);
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
}

void Scene::renderOneFrame(RenderContext &context) {
	ShadowResult shadows = shadowRenderer.render(context, this);

	context.setStage(RenderStage::Normal);
	context.activateViewport();
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->render(context);
	shadows.apply(terrain->prog);
	terrain->draw(*this);
	shadows.apply(prog);
	root->render(context);
}

Terrain *Scene::getTerrain() const {
	return terrain;
}

void Scene::onClick(glm::vec3 pos, Object *obj) {
	states.current().onClick(pos, obj, *this);
}

