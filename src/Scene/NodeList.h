#pragma once

#include "Node.h"

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

private:
	std::vector<Node *> nodes;
};


