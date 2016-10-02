#pragma once

#include <cstddef>
#include <GL/glew.h>

class VBO {
public:
	VBO(GLuint index);
	void bind();
	void setData(const char *data, size_t size);
private:
	GLuint id;
	GLuint bufferIndex;
};