#include <GL/glew.h>
#include "Shader.h"
#include "utils.h"

Shader::Shader(const char *file, GLenum type) {
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
		glDeleteShader(id);
		throw GlslCompileError(file, getGLLog(id));
	}
}
