#include "Light.h"

Light::Light(Program &shader, int id, LightType type) : id(id), type(type) {
	addListener(&shader);
}

void Light::render(RenderContext &context) {}

void Light::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	glm::vec4 pos = parent * glm::vec4(getPosition(), 1);
	worldPosition = pos;
	transformed(); //TODO: dont do this!
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

const glm::vec3 &Light::getDirection() const {
	return direction;
}

void Light::setDirection(const glm::vec3 &direction) {
	this->direction = direction;
}

const glm::vec3 Light::getWorldPosition() {
	return glm::vec3(worldPosition);
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
