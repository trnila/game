#include "NodeList.h"

void NodeList::render(RenderContext &context) {
	for (Node *node: nodes) {
		node->render(context);
	}
}

void NodeList::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	for(int i = 0; i < nodes.size(); i++) { //TODO: add removed/added objects to queue and add/remove at end of frame
		nodes[i]->update(diff, parent * getTransform());
	}
}

void NodeList::addNode(Node *node) {
	nodes.push_back(node);
	node->setParent(this);
}

void NodeList::removeNode(Node *node) {
	nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
	node->setParent(nullptr);
}

Mediator &NodeList::getMediator() {
	return mediator;
}
