#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "Type.h"

class VBO {
public:
	VBO(GLuint index);
	void bind();

	template<typename T>
	void setData(const T *data, size_t size, size_t blockSize) {
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T) * blockSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(bufferIndex, blockSize, Type<T>::value, GL_FALSE, 0, NULL);
	}
private:
	GLuint id;
	GLuint bufferIndex;
};