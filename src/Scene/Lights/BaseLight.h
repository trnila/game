#pragma once

#include "../Node.h"
#include "../../Utils/Color.h"

class BaseLight: public Node, public Subject<BaseLight> {
public:
	BaseLight(Program &shader, int id);
	~BaseLight();

	virtual void render(RenderContext &context) override;
	virtual void apply(Program& program) {
		send(program, "position", glm::vec4(getWorldPosition(), 1));
		send(program, "diffuseColor", getDiffuseColor());
		send(program, "specularColor", getSpecularColor());
		send(program, "attenuation", 0.3f);
	}

	const Color &getDiffuseColor() const;
	void setDiffuseColor(const Color &diffuseColor);
	const Color &getSpecularColor() const;
	void setSpecularColor(const Color &specularColor);

	int getId();
	void setActive(bool active);
	bool isActive();

	virtual Object* find(int id);

protected:
	virtual void transformed() override;

	template<typename T>
	void send(Program &program, std::string key, T data) {
		program.send(("lights[" + std::to_string(getId()) + "]." + key).c_str(), data);
	}

private:
	Color diffuseColor = Color(0, 0, 0);
	Color specularColor = Color(0, 0, 0);
	int id;
	bool active = true;
};


