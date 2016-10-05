#pragma once
#include "Shader.h"
#include "UniformVariable.h"

class Program {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	UniformVariable* bindUniformVariable(const char* variableName);
	void setMatrix(const char* var, const glm::mat4 &mat);

private:
	GLuint id;
};
