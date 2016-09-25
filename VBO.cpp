#include "VBO.h"

VBO::VBO() {
	glGenBuffers(1, &id);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::setData(const char *data, size_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

