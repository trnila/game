#pragma once

#include <GL/glew.h>
#include "Program.h"
#include "utils.h"
class FrameBuffer;

class Texture {
public:
	Texture(const char *file);
	Texture(GLuint type, int width, int height, int depth, int component);

	void set(int option, int value);
	void attachTo(FrameBuffer& frameBuffer);


	void bind();

private:
	GLuint id;
	int type;

	void create();
};


