#pragma once

#include <stdexcept>
#include <GL/glew.h>

class GlslCompileError: public std::runtime_error {
public:
	GlslCompileError(const char* source, std::string info): std::runtime_error(info) {
		this->source = source;
	}

	const char* getSource() {
		return source;
	}

private:
	const char* source;
};

class Shader {
public:
	Shader(const char *file, GLenum type);
	Shader() {}

	GLuint getId() {
		return id;
	}

private:
	GLuint id;
};



