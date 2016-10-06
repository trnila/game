#include <glm/gtc/type_ptr.hpp>
#include "Program.h"
#include "Camera.h"

Program::Program() {
	id = glCreateProgram();
	if(!id) {
		//TODO: check
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

UniformVariable *Program::bindUniformVariable(const char *variableName) {
	GLint uniformId;
	uniformId = glGetUniformLocation(id, variableName);
	if (uniformId == -1) {
		throw std::runtime_error("could not bind uniform variable");
	}

	return new UniformVariable(uniformId);
}

void Program::setMatrix(const char* var, const glm::mat4 &mat) {
	bindUniformVariable(var)->setData(mat);
}

void Program::notify(Camera &camera) {
	setMatrix("viewMatrix", camera.getTransform());
	setMatrix("projectionMatrix", camera.getPerspective());
}

void Program::setColor(float r, float g, float b) {
	GLint uniformId = glGetUniformLocation(id, "simpleColor");
	glUniform3fv(uniformId, 1, glm::value_ptr(glm::vec3(r, g, b)));
}
