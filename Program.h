#pragma once
#include <GL/glew.h>
#include "Shader.h"

class Program {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();

	GLint id;
};
