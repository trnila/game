#include "Program.h"

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