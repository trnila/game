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

Scene &NodeList::getScene() {
	return scene;
}

NodeList *NodeList::createGroup() {
	NodeList *list = new NodeList(scene);
	addNode(list);
	return list;
}

Object *NodeList::createEntity(const char *path) {
	Object *o = scene.getObjectFactory()->create(path);
	addNode(o);
	return o;
}

Object *NodeList::find(int id) {
	for (auto o : nodes) {
		Object* f = o->find(id);
		if (f) {
			return f;
		}
	}

	return nullptr;
}

BaseLight *NodeList::getLight(int id) {
	for (auto o : nodes) {
		BaseLight* l = dynamic_cast<BaseLight*>(o);
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
