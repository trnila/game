#include "Node.h"
#include "Logic.h"

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
