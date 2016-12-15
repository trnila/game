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

	std::vector<glm::vec3> points{
		glm::vec3{169.405823, 29.026913, 229.200348},
		glm::vec3{30.499992, 45.105583, 389.684570},
		glm::vec3{100.498253, 35.516335, 972.503296},
		glm::vec3{476.771637, 38.537769, 994.582825},
		glm::vec3{771.374695, 139.720657, 853.438232},
		glm::vec3{637.488220, 90.142654, 698.663940},
		glm::vec3{1196.538574, -30.870426, 604.598755},
		glm::vec3{1197.368164, -30.758410, 605.162354},
		glm::vec3{1116.818970, 57.950874, 135.645493},
		glm::vec3{840.971680, 74.526375, 377.371704},
		glm::vec3{169.405823, 29.026913, 229.200348},
	};
	camera->attachLogic("showcase", Bezier(points, 1, [](Node& node) -> void {
		node.removeLogic("showcase");
		node.setPosition(188.013016f, 100 + 33.348019f, 208.685776f);
		node.attachLogic(CamInit());
	}));
}

void Scene::createScene() {
	createTerrain();
	createObjects();
	createSkybox();

	camera.setZFar(20000);

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

