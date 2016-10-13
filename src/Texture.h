#pragma once

#include <GL/glew.h>

class Texture {
public:
	Texture(const char *file);


	void bind();

private:
	GLuint id;

};


