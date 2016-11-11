#pragma once
#include <string>
#include <fstream>
#include <sstream>

std::string preprocessShader(const char *path);
void checkOpenglError(const char *cmd, const char *file, int line);

#define GL_CHECK(cmd) do { \
		cmd; \
		checkOpenglError(#cmd, __FILE__, __LINE__); \
	} while(0);

std::string getGLLog(GLuint id);