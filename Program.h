#pragma once
#include "Shader.h"
#include "Observer.h"
#include "Camera.h"

class Program : public Observer<Camera> {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	void setMatrix(const char* var, const glm::mat4 &mat);

	void setColor(float r, float g, float b);

	virtual void updated(Camera &camera) override;

private:
	GLuint id;
};
