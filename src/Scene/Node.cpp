#include "Lights/BaseLight.h"
#include "Node.h"
#include "../Logic.h"
#include "NodeList.h"

void Node::updateLogic(float diff) {
	for(auto& cb: this->logic) {
		cb.update(*this, diff, *this->getParent()->getMediator().getScene());
	}
}

const glm::vec3 Node::getWorldPosition() {
	return worldPosition;
}

void Node::update(float diff, const glm::mat4 &parent) {
	glm::vec3 pos = glm::vec3(parent * glm::vec4(getPosition(), 1));

	if(worldPosition != pos) {
		worldPosition = pos;
		transformed();
	}

	updateLogic(diff);
}

NodeList *Node::getParent() const {
	return parent;
}

void Node::setParent(NodeList *parent) {
	Node::parent = parent;
}
