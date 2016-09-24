#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class UniformVariable {
public:
	UniformVariable(GLuint id): id(id) {}

	void setData(glm::mat4 &data) {
		glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(data));
	}
	

	
	
private:
	GLuint id;
};

class Program {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	UniformVariable* bindUniformVariable(const char* variableName) {		
		GLint uniformId;
		uniformId = glGetUniformLocation(id, variableName);
		if (uniformId == -1) {
			throw std::runtime_error("could not bind uniform variable");
		}

		return new UniformVariable(uniformId);
	}

private:
	GLint id;
};
