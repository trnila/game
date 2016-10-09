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

	glm::mat4 getTransform();
	void move(float x, float y, float z);
	void setPosition(float x, float y, float z);

	void setPosition(glm::vec3 pos);
	void rotate(float angle, float x, float y, float z);
	void setAngle(float angle);
	void addAngle(float angle);
	void multiplyScale(float x, float y, float z);
	glm::vec3 getScale();

	void setColor(float r, float g, float b);

	void setColor(glm::vec3 color);

	void setScale(float x, float y, float z);

	void setRotationPoint(float x, float y, float z);

	void setRotationPoint(glm::vec3 p);

	virtual void render(RenderContext &context) override;

	virtual void update(float diff) override;

	template<typename T, typename... Args>
	void attachLogic(Args... args) {
		logic = new T(*this, args...);
	}
private:
	glm::vec3 position;
	glm::vec3 rotateAxis;
	glm::vec3 rotatePoint;
	glm::vec3 scale;
	float angle;
	Model *model;
	Program &program;
	glm::vec3 color;
	Logic *logic = nullptr;
};
