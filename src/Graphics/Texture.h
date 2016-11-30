#pragma once

#include <GL/glew.h>
#include "Program.h"
#include "../Utils/utils.h"
class FrameBuffer;

class Texture {
public:
	Texture(const char *file);
	Texture(GLuint type, int width, int height, int depth, int component);
	Texture(int width, int height);
	Texture(GLuint type);
	~Texture();

	void set(int option, int value);
	void attachTo(FrameBuffer& frameBuffer);
	void bind();
	void setData(const uint8_t *data);

private:
	GLuint id;
	GLenum target;
	GLenum format; //GL_RGB, GL_DEPTH_COMPONENT
	GLenum type; //GL_UNSIGNED

	void create(GLenum target);

	int width;
	int height;
};


