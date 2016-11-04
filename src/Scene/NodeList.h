#pragma once

#include "Node.h"
#include "Light.h"

class NodeList : public Node {
public:
	virtual void render(RenderContext &context) override;
	virtual void update(float diff, const glm::mat4 &parent) override;
	void addNode(Node *node);
	void removeNode(Node *node);

	virtual Object* find(int id) {
		for (auto o : nodes) {
			Object* f = o->find(id);
			if (f) {
				return f;
			}
		}

		return nullptr;
	}

	virtual Light* getLight(int id) {
		for (auto o : nodes) {
			Light* l = dynamic_cast<Light*>(o);
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

private:
	std::vector<Node *> nodes;
};


