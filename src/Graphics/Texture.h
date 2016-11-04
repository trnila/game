#pragma once

#include <GL/glew.h>
#include "Program.h"
#include "../Utils/utils.h"
class FrameBuffer;

class Texture {
public:
	Texture(const char *file);
	Texture(GLuint type, int width, int height, int depth, int component);
	Texture(GLuint type);
	~Texture();

	void set(int option, int value);
	void attachTo(FrameBuffer& frameBuffer);


	void bind();

private:
	GLuint id;
	int type;

	void create();
};


