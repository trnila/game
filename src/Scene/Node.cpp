#include "Light.h"
#include "Node.h"
#include "../Logic.h"

void Node::updateLogic(float diff) {
	if (logic) {
		logic->update(diff);
	}
}

Node::~Node() {
	if (logic) {
		delete logic;
	}
}

const glm::vec3 Node::getWorldPosition() {
	return worldPosition;
}

void Node::update(float diff, const glm::mat4 &parent) {
	glm::vec4 pos = parent * glm::vec4(getPosition(), 1);

	if(worldPosition != pos) {
		worldPosition = pos;
		transformed();
	}

	updateLogic(diff);
}
