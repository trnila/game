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

private:
	Program &shader;
	Color diffuseColor = Color(0, 0, 0);
	Color specularColor = Color(0, 0, 0);
};


