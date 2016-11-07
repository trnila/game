#include <GL/glew.h>
#include <iostream>
#include <stdlib.h>
#include "utils.h"
#include "Formatter.h"

std::string getFileContents(const char* path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error(Formatter() << "Shader does not exist: " << path);
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return content;
}

void checkOpenglError(const char *cmd, const char *file, int line) {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << " " << file << line << cmd << std::endl;
		abort();
	}
}

std::string getGLLog(GLuint id) {
	GLint log_length = 0;
	if (glIsShader(id)) {
		GL_CHECK(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length));
	}
	else if (glIsProgram(id)) {
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
	}

	char* log = new char[log_length];

	if (glIsShader(id)) {
		glGetShaderInfoLog(id, log_length, NULL, log);
	} else if (glIsProgram(id)) {
		glGetProgramInfoLog(id, log_length, NULL, log);
	} else {

	}

	std::string result = std::string(log);
	delete[] log;
	return result;
}