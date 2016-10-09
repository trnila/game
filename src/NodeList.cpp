
#include "NodeList.h"

void NodeList::render(RenderContext &context) {
	for (Node *node: nodes) {
		node->render(context);
	}
}

void NodeList::update(float diff) {
	for (Node *node: nodes) {
		node->update(diff);
	}
}

void NodeList::addNode(Node *node) {
	nodes.push_back(node);
}

void NodeList::removeNode(Node *node) {
	//TODO: do this!
}
