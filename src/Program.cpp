#include <glm/gtc/type_ptr.hpp>
#include "Program.h"
#include "Light.h"
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
		throw GlslCompileError("linking", getGLLog(id));
	}
}

void Program::use() {
	GL_CHECK(glUseProgram(id));
}

void Program::setMatrix(const char* var, const glm::mat4 &mat) {
	use();
	GLint uniformId = glGetUniformLocation(id, var);
	GL_CHECK(glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(mat)));
}

void Program::updated(Camera &camera) {
	setMatrix("viewMatrix", camera.getTransform());
	setMatrix("projectionMatrix", camera.getPerspective());

	GLint uniformId = glGetUniformLocation(id, "cameraPos");
	GL_CHECK(glUniform3fv(uniformId, 1, glm::value_ptr(camera.getPosition())));
}

void Program::setColor(float r, float g, float b) {
	sendVector("simpleColor", glm::vec3(r, g, b));
}

void Program::setBool(const char *var, bool val) {
	use();
	GLint uniformId = glGetUniformLocation(id, var);
	GL_CHECK(glUniform1i(uniformId, val));
}

void Program::updated(Light &obj) {
	std::string prefix = "lights[" + std::to_string(obj.getId()) + "].";

	sendVector((prefix + "position").c_str(), obj.getWorldPosition());
	sendVector((prefix + "diffuseColor").c_str(), obj.getDiffuseColor());
	sendVector((prefix + "specularColor").c_str(), obj.getSpecularColor());
}

void Program::sendVector(const char *name, const glm::vec3 &vec) {
	use();
	GLint uniformId = glGetUniformLocation(id, name);
	if(!uniformId) {
		printf("failed sending %s\n", name);
	}
	GL_CHECK(glUniform3fv(uniformId, 1, glm::value_ptr(vec)));
}

void Program::setAmbientColor(const Color &color) {
	sendVector("ambientColor", color);
}

void Program::useTexture(const char *name, Texture &texture, int pos) {
	GLint location = glGetUniformLocation(id, name);

	GL_CHECK(glActiveTexture(GL_TEXTURE0 + pos));
	texture.bind();
	GL_CHECK(glUniform1i(location, pos));
}

void Program::sendFloat(const char *name, float v) {
	use();
	GLint uniformId = glGetUniformLocation(id, name);
	if(!uniformId) {
		printf("failed sending %s\n", name);
	}
	GL_CHECK(glUniform1f(uniformId, v));
}
