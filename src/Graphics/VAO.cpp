
#include "VAO.h"

VAO::VAO() {
	GL_CHECK(glGenVertexArrays(1, &id));
}

void VAO::enableAttrib(GLuint id) {
	GL_CHECK(glEnableVertexAttribArray(id));
}

VAO::~VAO() {
	GL_CHECK(glDeleteVertexArrays(1, &id));
}
