
#include "BaseLight.h"
#include "SpotLight.h"

float SpotLight::getConeAngle() const {
	return coneAngle;
}

void SpotLight::setConeAngle(float coneAngle) {
	SpotLight::coneAngle = coneAngle;
	transformed();
}

SpotLight::SpotLight(Mediator &shader, int id) : BaseLight(shader, id) {}

const glm::vec3 &SpotLight::getDirection() const {
	return direction;
}

void SpotLight::setDirection(const glm::vec3 &direction) {
	this->direction = direction;
}

void SpotLight::apply(Program &program) {
	BaseLight::apply(program);
	send(program, "coneDirection", getDirection());
	send(program, "coneAngle", getConeAngle());
}
