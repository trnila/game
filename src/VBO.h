#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "Type.h"
#include <typeinfo>

#include <stdio.h>
class VBO {
public:
	VBO();
	void bind();
	void unbind();

	template<typename T>
	void setData(const T *data, size_t size, size_t blockSize) {
		bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T) * blockSize, data, GL_STATIC_DRAW);
	}

	template<typename T>
	void setPointer(GLuint layoutPos, int offset) {
		glVertexAttribPointer(layoutPos, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offset);
	}

private:
	GLuint id;
	size_t blockSize;
};