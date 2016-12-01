#pragma once


#include "../Node.h"

class DirectionalLight: public BaseLight {
public:
	DirectionalLight(Mediator &shader, int id);

	const glm::vec3 &getDir() const;
	void setDir(const glm::vec3 &direction);

	void apply(Program &program) override;

private:
	glm::vec3 dir;
};


