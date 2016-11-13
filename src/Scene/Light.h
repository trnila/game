#pragma once

#include "Node.h"
#include "../Utils/Color.h"

enum class LightType {
	Point,
	Directional,
	SpotLight
};

class Light: public Node, public Subject<Light> {
public:
	Light(Program &shader, int id, LightType type);
	~Light();

	virtual void render(RenderContext &context) override;

	const Color &getDiffuseColor() const;
	void setDiffuseColor(const Color &diffuseColor);
	const Color &getSpecularColor() const;
	void setSpecularColor(const Color &specularColor);
	const glm::vec3 &getDirection() const;
	void setDirection(const glm::vec3 &direction);

	int getId();
	void setActive(bool active);
	bool isActive();

	LightType getType() const;
	void setType(LightType type);

	virtual Object* find(int id);

protected:
public:
	float getConeAngle() const;

	void setConeAngle(float coneAngle);

protected:
	virtual void transformed() override;

private:
	Color diffuseColor = Color(0, 0, 0);
	Color specularColor = Color(0, 0, 0);
	glm::vec3 direction;
	int id;
	bool active = true;
	LightType type;
	float coneAngle = 360;
};


