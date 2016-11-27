
#include "BaseLight.h"
#include "DirectionalLight.h"

const glm::vec3 &DirectionalLight::getDirection() const {
	return direction;
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
	this->direction = direction;
	Subject::notify();
}

DirectionalLight::DirectionalLight(Program &shader, int id) : BaseLight(shader, id) {}

void DirectionalLight::apply(Program &program) {
	BaseLight::apply(program);
	send(program, "position", glm::vec4(getDirection(), 0));
}
