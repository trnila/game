#pragma once
#include "../Node.h"
#include "BaseLight.h"

class SpotLight: public BaseLight {
public:
	SpotLight(Scene &shader, int id);

	float getConeAngle() const;
	void setConeAngle(float coneAngle);
	const glm::vec3 &getDirection() const;
	void setDirection(const glm::vec3 &direction);

	void apply(Program &program) override;

private:
	float coneAngle = 360;
	glm::vec3 direction = glm::vec3(0, 0, 0);
};


