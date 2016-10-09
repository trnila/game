#include <glm/gtc/type_ptr.hpp>
#include "Program.h"

Program::Program() {
	id = glCreateProgram();
	if(!id) {
		throw std::runtime_error("Could not create program!");
	}
}

void Program::attach(Shader &shader) {
	glAttachShader(id, shader.getId());
}

void Program::link() {
	glLinkProgram(id);

	GLint link_ok;
	glGetProgramiv(id, GL_LINK_STATUS, &link_ok);
	if(!link_ok) {
		throw GlslCompileError("", "unable to link");
	}
}

void Program::use() {
	glUseProgram(id);
}

void Program::setMatrix(const char* var, const glm::mat4 &mat) {
	GLint uniformId = glGetUniformLocation(id, var);
	if (uniformId == -1) {
		throw std::runtime_error("could not bind uniform variable");
	}

	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::updated(Camera &camera) {
	setMatrix("viewMatrix", camera.getTransform());
	setMatrix("projectionMatrix", camera.getPerspective());
}

void Program::setColor(float r, float g, float b) {
	GLint uniformId = glGetUniformLocation(id, "simpleColor");
	glUniform3fv(uniformId, 1, glm::value_ptr(glm::vec3(r, g, b)));
}
