#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Model.h"
#include "RenderContext.h"
#include "Node.h"

class Logic;

class Object : public Node {
public:
	Object(Model *model, Program& program);
	~Object();
	void setColor(float r, float g, float b);
	void setColor(glm::vec3 color);
	virtual void render(RenderContext &context) override;
	virtual void update(float diff) override;

	template<typename T, typename... Args>
	void attachLogic(Args... args) {
		logic = new T(*this, args...);
	}
private:
	Model *model;
	Program &program;
	glm::vec3 color;
	Logic *logic = nullptr;
};
