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

private:
	GLuint id;
};
