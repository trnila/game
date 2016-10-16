#include "VBO.h"

VBO::VBO() {
	glGenBuffers(1, &id);
}

VBO::~VBO() {
	//glDeleteBuffers(1, &id);
}