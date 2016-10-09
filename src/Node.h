#pragma once

#include "RenderContext.h"
#include "Transform.h"

class Node : public Transform {
public:
	virtual void render(RenderContext &context) = 0;

	virtual void update(float diff) = 0;
};


