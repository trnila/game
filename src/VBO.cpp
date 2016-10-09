#include "VBO.h"

VBO::VBO(GLuint index) : bufferIndex(index) {
	glGenBuffers(1, &id);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
