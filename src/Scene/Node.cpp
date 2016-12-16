#include "Lights/BaseLight.h"
#include "../Logic.h"

void Node::updateLogic(float diff) {
	for (std::string& name : toRemoveLogic) {
		logic.erase(std::remove_if(logic.begin(), logic.end(), [&](const LogicComponent& comp) -> bool {
			return comp.getName() == name;
		}));
	}
	toRemoveLogic.clear();

	for(int i = 0; i < logic.size(); i++) {
		logic[i].update(*this, diff, this->getParent()->getScene());
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
