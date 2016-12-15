#pragma once

#include "Node.h"
#include "Lights/BaseLight.h"
#include "../Scene.h"

class NodeList : public Node {
public:
	NodeList(Scene &scene): scene(scene) {
	}

	virtual void render(RenderContext &context) override;
	virtual void update(float diff, const glm::mat4 &parent) override;
	void addNode(Node *node);
	void removeNode(Node *node);

	NodeList* createGroup();

	Object* createEntity(const char *path);

	template<typename T>
	T* createLight(int id) {
		static_assert(std::is_base_of<BaseLight, T>::value, "Parameter is not light!");
		T* light = new T(scene, id);
		addNode(light);
		return light;
	}

	virtual Object* find(int id);

	virtual BaseLight* getLight(int id);

	Scene &getScene();

private:
	std::vector<Node *> nodes;
	Scene &scene;
};
