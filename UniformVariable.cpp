#include <glm/gtc/type_ptr.hpp>
#include "UniformVariable.h"

UniformVariable::UniformVariable(GLint id) : id(id) {}

void UniformVariable::setData(const glm::mat4 &data) {
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(data));
}
