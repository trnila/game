#include "VBO.h"

VBO::VBO(GLuint index) : bufferIndex(index) {
	glGenBuffers(1, &id);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::setData(const char *data, size_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}
