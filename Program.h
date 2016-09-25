#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
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
	GLint id;
};
