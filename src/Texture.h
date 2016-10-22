#pragma once

#include <GL/glew.h>
#include "Program.h"

class Texture {
public:
	Texture(const char *file);


	void bind(Program &program);

private:
	GLuint id;

};


