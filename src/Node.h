#pragma once

#include "RenderContext.h"
#include "Transform.h"

class Logic;

class Node : public Transform {
public:
	virtual ~Node() {
		if (logic) {
			delete logic;
		}
	}

	virtual void render(RenderContext &context) = 0;
	virtual void update(float diff, const glm::mat4 parent) = 0;

	template<typename T, typename... Args>
	void attachLogic(Args... args) {
		logic = new T(*this, args...);
	}

protected:
	Logic *logic = nullptr;
};


