#include "Light.h"

Light::Light(Program &shader) : shader(shader) {}

void Light::render(RenderContext &context) {

}

void Light::update(float diff, const glm::mat4 &parent) {
	updateLogic(diff);

	glm::vec4 pos = parent * glm::vec4(getPosition(), 1);

	shader.setLight(pos);
}
