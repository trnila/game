#pragma once

#include <GL/glew.h>

class VAO {
public:
	VAO();
	void bind();
	void enableAttrib(GLuint id);

private:
	unsigned int id;
};