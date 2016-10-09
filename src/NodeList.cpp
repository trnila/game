
#include "NodeList.h"
#include "Object.h"

void NodeList::render(RenderContext &context) {
	for (Node *node: nodes) {
		node->render(context);
	}
}

void NodeList::update(float diff, const glm::mat4 parent) {
	for (Node *node: nodes) {
		node->update(diff, parent * getTransform());
	}
}

void NodeList::addNode(Node *node) {
	nodes.push_back(node);
}

void NodeList::removeNode(Node *node) {
	//TODO: do this!
}