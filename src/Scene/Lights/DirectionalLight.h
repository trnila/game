#pragma once


#include "../Node.h"

class DirectionalLight: public BaseLight {
public:
	DirectionalLight(Program &shader, int id);

	const glm::vec3 &getDirection() const;
	void setDirection(const glm::vec3 &direction);

	void apply(Program &program) override;

private:
	glm::vec3 direction;
};


