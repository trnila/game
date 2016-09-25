#pragma once

#include <GL/glew.h>

class VAO {
public:
	VAO();
	void bind();
	void enableAttrib(int id);

private:
	unsigned int id;
};