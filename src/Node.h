#pragma once

#include "RenderContext.h"

class Node {
public:
	virtual void render(RenderContext &context) = 0;

	virtual void update(float diff) = 0;
};


