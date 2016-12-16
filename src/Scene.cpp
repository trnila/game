#include <glm/ext.hpp>
#include "Scene.h"
#include "Scene/Lights/BaseLight.h"
#include "States.h"
#include "State.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Scene/Lights/PointLight.h"
#include "Scene/Lights/SpotLight.h"
#include "GeneratedTerrain.h"
#include "Panel.h"
#include "Factory.h"
#include "Game.h"

Scene::Scene(Factory *factory) {
	initResources();
	createScene();

	factory->fillScene(*this);

	terrain = (Terrain*) getRootNode().findBy([](Node* node) -> bool {
		return dynamic_cast<Terrain*>(node) != nullptr;
	});
}

void Scene::createScene() {
	createObjects();
	getRootNode().getScene().setAmbientLight(Color(0.1, 0.1, 0.1));
}

void Scene::createObjects() {
}

void Scene::initResources() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	factory = new ObjectFactory(prog, shadowRenderer.program);
	root = new NodeList(*this);
	registerProgram(&prog);

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

	//shadows.apply(terrain->prog); //TODO: shadows?
	//terrain->draw(*this);
	shadows.apply(prog);
	root->render(context);
}

Terrain *Scene::getTerrain() const {
	return terrain;
}

void Scene::onClick(glm::vec3 pos, Object *obj) {
	states.current().onClick(pos, obj, *this);
}

