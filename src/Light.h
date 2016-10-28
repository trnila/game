#pragma once

#include "Node.h"
#include "Color.h"

class Light: public Node, public Subject<Light> {
public:
	Light(Program &shader);
	~Light();

	virtual void render(RenderContext &context) override;
	virtual void update(float diff, const glm::mat4 &parent) override;

	const Color &getDiffuseColor() const;

	void setDiffuseColor(const Color &diffuseColor);

	const Color &getSpecularColor() const;

	void setSpecularColor(const Color &specularColor);

	const glm::vec3 &getDirection() const;

	void setDirection(const glm::vec3 &direction);

	const glm::vec3 getWorldPosition();

private:
	Program &shader;
	Color diffuseColor = Color(0, 0, 0);
	Color specularColor = Color(0, 0, 0);
	glm::vec3 direction;
	glm::vec4 worldPosition;
};


