#pragma once


#include "../Transformable.h"
#include "../Graphics/RenderContext.h"

class Logic;
class Object;

class Node : public Transformable {
public:
	virtual ~Node();

	virtual void render(RenderContext &context) = 0;
	virtual void update(float diff, const glm::mat4 &parent);

	template<typename T, typename... Args>
	void attachLogic(Args... args) {
		logic = new T(*this, args...);
	}

	void updateLogic(float diff);

	virtual Object* find(int id) = 0;

	const glm::vec3 getWorldPosition();

private:
	Logic *logic = nullptr;
	glm::vec4 worldPosition;
};


