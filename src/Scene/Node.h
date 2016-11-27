#pragma once


#include <functional>
#include "../Transformable.h"
#include "../Graphics/RenderContext.h"

class Logic;
class Object;
class NodeList;
class Scene;

class Node : public Transformable {
public:
	typedef std::function<void(Node&, float, Scene&)> LogicFunctor;

	virtual void render(RenderContext &context) = 0;
	virtual void update(float diff, const glm::mat4 &parent);

	void attachLogic(const LogicFunctor &functor) {
		logic.push_back(functor);
	}

	NodeList *getParent() const;
	void setParent(NodeList *parent);

	void updateLogic(float diff);
	virtual Object* find(int id) = 0;
	const glm::vec3 getWorldPosition();

private:
	std::vector<LogicFunctor> logic;
	glm::vec3 worldPosition;
	NodeList *parent = nullptr;
};


