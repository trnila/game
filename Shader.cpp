#include <GL/glew.h>
#include "Shader.h"
#include "utils.h"

Shader::Shader(GLenum type, const char *file) {
	id = glCreateShader(type);
	if(!id) {
		throw std::runtime_error("Could not create shader");
	}

	std::string source = getFileContents(file);
	const GLchar *addr = (GLchar*) source.data();
	glShaderSource(id, 1, &addr, NULL);

	glCompileShader(id);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		GLint log_length = 0;
		if (glIsShader(id)) {
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		} else if (glIsProgram(id)) {
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
		}

		char* log = new char[log_length];

		if (glIsShader(id))
			glGetShaderInfoLog(id, log_length, NULL, log);
		else if (glIsProgram(id))
			glGetProgramInfoLog(id, log_length, NULL, log);

		glDeleteShader(id);
		GlslCompileError exception(file, std::string(log));
		delete[] log;
		throw exception;
	}
}
