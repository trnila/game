#include <glm/ext.hpp>
#include "Scene.h"

Scene::Scene(Factory *factory) {
	initResources();
	getRootNode().getScene().setAmbientLight(Color(0.1, 0.1, 0.1));

	factory->fillScene(*this);
	getActiveCamera().addListener(&prog);

	terrain = (Terrain*) getRootNode().findBy([](Node* node) -> bool {
		return dynamic_cast<Terrain*>(node) != nullptr;
	});
}

void Scene::initResources() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	factory = new ObjectFactory(prog, shadowRenderer.program);
	root = new NodeList(*this);
	registerProgram(&prog);
}

void Scene::update(float time) {
	glm::mat4 parent(1.0f);
	root->update(time, parent);
}

void Scene::renderOneFrame(RenderContext &context) {
	ShadowResult result = shadowRenderer.render(context, this);
	context.setResult(&result);

	context.setStage(RenderStage::Normal);
	context.activateViewport();
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//shadows.apply(terrain->prog); //TODO: shadows?
	//terrain->draw(*this);
	root->render(context);
}

Terrain *Scene::getTerrain() const {
	return terrain;
}
