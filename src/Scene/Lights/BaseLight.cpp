#include "BaseLight.h"

BaseLight::BaseLight(Program &shader, int id) : id(id) {
	addListener(&shader);
}

void BaseLight::render(RenderContext &context) {}

const Color &BaseLight::getDiffuseColor() const {
	return diffuseColor;
}

void BaseLight::setDiffuseColor(const Color &diffuseColor) {
	this->diffuseColor = diffuseColor;
	notify();
}

const Color &BaseLight::getSpecularColor() const {
	return specularColor;
}

void BaseLight::setSpecularColor(const Color &specularColor) {
	this->specularColor = specularColor;
	notify();
}

void BaseLight::transformed() {
	Transformable::transformed();
	notify();
}

int BaseLight::getId() {
	return id;
}

void BaseLight::setActive(bool active) {
	this->active = active;
	notify();
}

bool BaseLight::isActive() {
	return active;
}

BaseLight::~BaseLight() {
	setActive(false);
}

Object *BaseLight::find(int id) {
	return nullptr;
}

float BaseLight::getAttenuation() const {
	return attenuation;
}

void BaseLight::setAttenuation(float attenuation) {
	BaseLight::attenuation = attenuation;
}
