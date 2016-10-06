#pragma once
#include "Shader.h"
#include "UniformVariable.h"
#include "Observer.h"

class Program: public Observer {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	UniformVariable* bindUniformVariable(const char* variableName);
	void setMatrix(const char* var, const glm::mat4 &mat);

	void setColor(float r, float g, float b);

	virtual void notify(Camera &camera) override;

private:
	GLuint id;
};
