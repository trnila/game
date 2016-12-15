
#include "BaseLight.h"
#include "DirectionalLight.h"

const glm::vec3 &DirectionalLight::getDir() const {
	return dir;
}

void DirectionalLight::setDir(const glm::vec3 &direction) {
	this->dir = direction;
	transformed();
}

DirectionalLight::DirectionalLight(Scene &shader, int id) : BaseLight(shader, id) {}

void DirectionalLight::apply(Program &program) {
	BaseLight::apply(program);
	send(program, "position", glm::vec4(getDir(), 0));
}
