
#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &id);
}

void VAO::bind() {
	glBindVertexArray(id);
}

void VAO::enableAttrib(GLuint id) {
	glEnableVertexAttribArray(id);
}
