#include "BaseLight.h"
#include "../../Mediator.h"

BaseLight::BaseLight(Mediator &mediator, int id) : mediator(mediator), id(id) {
}

void BaseLight::render(RenderContext &context) {}

const Color &BaseLight::getDiffuseColor() const {
	return diffuseColor;
}

void BaseLight::setDiffuseColor(const Color &diffuseColor) {
	this->diffuseColor = diffuseColor;
	transformed();
}

const Color &BaseLight::getSpecularColor() const {
	return specularColor;
}

void BaseLight::setSpecularColor(const Color &specularColor) {
	this->specularColor = specularColor;
	transformed();
}

void BaseLight::transformed() {
	Transformable::transformed();
	mediator.lightChanged(this);
}

int BaseLight::getId() {
	return id;
}

void BaseLight::setActive(bool active) {
	this->active = active;
	transformed();
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
