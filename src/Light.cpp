#include "Light.h"

Light::Light(Program &shader, int id) : id(id) {
	addListener(&shader);
}

void Light::render(RenderContext &context) {

}

void Light::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	glm::vec4 pos = parent * glm::vec4(getPosition(), 1);
	worldPosition = pos;
}

const Color &Light::getDiffuseColor() const {
	return diffuseColor;
}

void Light::setDiffuseColor(const Color &diffuseColor) {
	this->diffuseColor = diffuseColor;
	notify();
}

const Color &Light::getSpecularColor() const {
	return specularColor;
}

void Light::setSpecularColor(const Color &specularColor) {
	this->specularColor = specularColor;
	notify();
}

Light::~Light() {
	setActive(false);
}

const glm::vec3 &Light::getDirection() const {
	return direction;
}

void Light::setDirection(const glm::vec3 &direction) {
	Light::direction = direction;
}

const glm::vec3 Light::getWorldPosition() {
	return worldPosition;
}

void Light::transformed() {
	Transformable::transformed();
	notify();
}

int Light::getId() {
	return id;
}

void Light::setActive(bool active) {
	this->active = active;
	notify();
}

bool Light::isActive() {
	return active;
}
