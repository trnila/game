#include "Light.h"

Light::Light(Program &shader, int id, LightType type) : id(id), type(type) {
	addListener(&shader);
}

void Light::render(RenderContext &context) {}

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

const glm::vec3 &Light::getDirection() const {
	return direction;
}

void Light::setDirection(const glm::vec3 &direction) {
	this->direction = direction;
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

Light::~Light() {
	setActive(false);
}

LightType Light::getType() const {
	return type;
}

void Light::setType(LightType type) {
	Light::type = type;
}

float Light::getConeAngle() const {
	return coneAngle;
}

void Light::setConeAngle(float coneAngle) {
	Light::coneAngle = coneAngle;
}

Object *Light::find(int id) {
	return nullptr;
}
