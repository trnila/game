#include <glm/gtc/type_ptr.hpp>
#include "Program.h"
#include "../Scene/Lights/BaseLight.h"
#include "Texture.h"

Program::Program() {
	id = glCreateProgram();
	if(!id) {
		throw std::runtime_error("Could not create program!");
	}
}

void Program::attach(Shader &shader) {
	GL_CHECK(glAttachShader(id, shader.getId()));
}

void Program::link() {
	GL_CHECK(glLinkProgram(id));

	GLint link_ok;
	GL_CHECK(glGetProgramiv(id, GL_LINK_STATUS, &link_ok));
	if(!link_ok) {
		glDeleteShader(id);
		throw GlslCompileError("linking", getGLLog(id), "");
	}
}

void Program::use() {
	GL_CHECK(glUseProgram(id));
}

void Program::updated(Camera &camera) {
	send("viewMatrix", camera.getLookAt());
	send("projectionMatrix", camera.getPerspective());
	send("cameraPos", camera.getPosition());
}

void Program::setColor(float r, float g, float b) {
	send("simpleColor", glm::vec3(r, g, b));
}

void Program::updated(BaseLight &obj) {
	if(obj.isActive()) {
		activeLights |= 1 << obj.getId();
		obj.apply(*this);
	} else {
		activeLights &= ~(1 << obj.getId());
	}

	send("activeLights", activeLights);
}

void Program::send(const char *name, const glm::vec3 &vec) {
	GL_CHECK(glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}

void Program::setAmbientColor(const Color &color) {
	send("ambientColor", color);
}

void Program::send(const char *name, float v) {
	GL_CHECK(glUniform1f(getUniformLocation(name), v));
}

void Program::useTexture(const char *name, Texture &texture, int pos) {
	GLint location = getUniformLocation(name);

	GL_CHECK(glActiveTexture(GL_TEXTURE0 + pos));
	texture.bind();
	GL_CHECK(glUniform1i(location, pos));
}

void Program::send(const char *name, int value) {
	GL_CHECK(glUniform1i(getUniformLocation(name), value));
}

void Program::send(const char *name, const glm::vec4 &vec) {
	GL_CHECK(glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}

void Program::send(const char* var, const glm::mat4 &mat) {
	GL_CHECK(glUniformMatrix4fv(getUniformLocation(var), 1, GL_FALSE, glm::value_ptr(mat)));
}

void Program::send(const char *var, bool val) {
	GL_CHECK(glUniform1i(getUniformLocation(var), val));
}

int Program::getUniformLocation(const char * name) {
	use();
	GLint uniformId = glGetUniformLocation(id, name);
	if (!uniformId) {
		//printf("failed sending %s\n", name);
	}
	return uniformId;
}

void Program::send(const char *name, const glm::vec2 vec) {
	GL_CHECK(glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}
