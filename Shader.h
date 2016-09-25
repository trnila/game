#pragma once

#include <GL/gl.h>
#include <stdexcept>

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
	Shader(GLenum type, const char *file);

	GLuint getId() {
		return id;
	}

private:
	GLuint id;
};



