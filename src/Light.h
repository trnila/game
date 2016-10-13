#pragma once

#include "Node.h"

class Light: public Node {
public:
	Light(Program &shader);

	virtual void render(RenderContext &context) override;
	virtual void update(float diff, const glm::mat4 &parent) override;

private:
	Program &shader;
};


