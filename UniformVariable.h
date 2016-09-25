
#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformVariable {
public:
	UniformVariable(GLuint id): id(id) {}

	void setData(glm::mat4 &data) {
		glUniformMatrix4fv(id, 1, GL_FALSE, value_ptr(data));
	}

private:
	GLuint id;
};