#include "NodeList.h"

void NodeList::render(RenderContext &context) {
	for (Node *node: nodes) {
		node->render(context);
	}
}

void NodeList::update(float diff, const glm::mat4 parent) {
	updateLogic(diff);

	for (Node *node: nodes) {
		node->update(diff, parent * getTransform());
	}
}

void NodeList::addNode(Node *node) {
	nodes.push_back(node);
}

void NodeList::removeNode(Node *node) {
	nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}