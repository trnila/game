#include "VBO.h"

VBO::VBO() {
	GL_CHECK(glGenBuffers(1, &id));
}

VBO::~VBO() {
	//GL_CHECK(glDeleteBuffers(1, &id));
}