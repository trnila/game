#pragma once

#include "Node.h"
#include "Lights/BaseLight.h"

class NodeList : public Node {
public:
	NodeList(Mediator &mediator): mediator(mediator) {
	}

	virtual void render(RenderContext &context) override;
	virtual void update(float diff, const glm::mat4 &parent) override;
	void addNode(Node *node);
	void removeNode(Node *node);

	NodeList* createGroup() {
		NodeList *list = new NodeList(mediator);
		addNode(list);
		return list;
	}

	Object* createEntity(const char *path) {
		Object *o = mediator.getObjectFactory()->create(path);
		addNode(o);
		return o;
	}

	template<typename T>
	T* createLight(int id) {
		static_assert(std::is_base_of<BaseLight, T>::value, "Parameter is not light!");
		T* light = new T(mediator, id);
		addNode(light);
		return light;
	}

	virtual Object* find(int id) {
		for (auto o : nodes) {
			Object* f = o->find(id);
			if (f) {
				return f;
			}
		}

		return nullptr;
	}

	virtual BaseLight* getLight(int id) {
		for (auto o : nodes) {
			BaseLight* l = dynamic_cast<BaseLight*>(o);
			if (l && l->getId() == id) {
				return l;
			}

			if(NodeList* list = dynamic_cast<NodeList*>(o)) {
				l = list->getLight(id);
				if(l) {
					return l;
				}
			}
		}

		return nullptr;
	}

	Mediator &getMediator();

private:
	std::vector<Node *> nodes;
	Mediator &mediator;
};
