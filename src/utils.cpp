#include <GL/glew.h>
#include <iostream>
#include "utils.h"

std::string getFileContents(const char* path) {
	std::ifstream file(path);

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
