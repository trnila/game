#pragma once

#include "RenderContext.h"
#include "Transform.h"

class Logic;

class Node : public Transform {
public:
	virtual ~Node();

	virtual void render(RenderContext &context) = 0;
	virtual void update(float diff, const glm::mat4 parent) = 0;

	template<typename T, typename... Args>
	void attachLogic(Args... args) {
		logic = new T(*this, args...);
	}

	void updateLogic(float diff);

private:
	Logic *logic = nullptr;
};


