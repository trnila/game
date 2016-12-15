#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

void checkOpenglError(const char *cmd, const char *file, int line);

float rand_float(float a, float b);

#define GL_CHECK(cmd) do { \
		checkOpenglError("before", __FILE__, __LINE__); \
		cmd; \
		checkOpenglError(#cmd, __FILE__, __LINE__); \
	} while(0);

std::string getGLLog(GLuint id);