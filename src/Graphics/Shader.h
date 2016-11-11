#pragma once

#include <stdexcept>
#include <GL/glew.h>

class GlslCompileError: public std::runtime_error {
public:
	GlslCompileError(const char *source, std::string info) : runtime_error(std::string(source) + ":" + info) {
		this->source = source;
		this->info = info;
	}

	const char* getSource() {
		return source;
	}

private:
	const char* source;
	std::string info;
};

class Shader {
public:
	Shader(const char *file, GLenum type);

	GLuint getId() {
		return id;
	}

private:
	GLuint id;

	std::string preprocessShader(const char *path);
};



