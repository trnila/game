#include "Light.h"

Light::Light(Program &shader) : shader(shader) {}

void Light::render(RenderContext &context) {

}

void Light::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);
	shader.setLight(getPosition());
}
