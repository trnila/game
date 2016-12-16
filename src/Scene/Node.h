#pragma once


#include <functional>
#include <vector>
#include "../Transformable.h"
#include "../Graphics/RenderContext.h"

class Logic;
class Object;
class NodeList;
class Scene;
class Node;

typedef std::function<void(Node&, float, Scene&)> LogicFunctor;

class LogicComponent {
public:
	LogicComponent(std::string name, const LogicFunctor &callback) : name(name), callback(callback), active(true) {}

	void update(Node& node, float dt, Scene& root) {
		if(active) {
			callback(node, dt, root);
		}
	}

	const std::string &getName() const {
		return name;
	}

	void setName(const std::string &name) {
		LogicComponent::name = name;
	}

	bool isActive() const {
		return active;
	}

	void setActive(bool active) {
		this->active = active;
	}

private:
	std::string name;
	bool active;
	LogicFunctor callback;
};

class Node : public Transformable {
public:


	virtual void render(RenderContext &context) = 0;
	virtual void update(float diff, const glm::mat4 &parent);

	void attachLogic(const LogicFunctor &functor) {
		attachLogic("_unnamed", functor);
	}

	void attachLogic(const std::string &name, const LogicFunctor &functor) {
		logic.push_back(LogicComponent(name, functor));
	}

	void removeLogic(const std::string &name) {
		logic.erase(std::remove_if(logic.begin(), logic.end(), [&](const LogicComponent& comp) -> bool {
			return comp.getName() == name;
		}));
	}

	void removeAllLogic() {
		logic.clear();
	}

	NodeList *getParent() const;
	void setParent(NodeList *parent);

	void updateLogic(float diff);
	virtual Object* find(int id) = 0;
	const glm::vec3 getWorldPosition();

	virtual Node* findBy(std::function<bool(Node*)> predicate) {
		if(predicate(this)) {
			return this;
		}
		return nullptr;
	}

private:
	std::vector<LogicComponent> logic;
	glm::vec3 worldPosition;
	NodeList *parent = nullptr;
};


