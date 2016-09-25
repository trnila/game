#pragma once
#include <glm/mat4x4.hpp>
#include <GL/glew.h>

class UniformVariable {
public:
	UniformVariable(GLint id);

	void setData(glm::mat4 &data);

private:
	GLint id;
};