#include <GL/glew.h>
#include "Shader.h"
#include "../Utils/utils.h"

Shader::Shader(const char *file, GLenum type) {
	id = glCreateShader(type);
	if(!id) {
		throw std::runtime_error("Could not create shader");
	}

	std::string source = getFileContents(file);
	const GLchar *addr = (GLchar*) source.data();
	GL_CHECK(glShaderSource(id, 1, &addr, NULL));

	GL_CHECK(glCompileShader(id));
	GLint compile_ok = GL_FALSE;
	GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &compile_ok));
	if (compile_ok == GL_FALSE) {
		std::string error = getGLLog(id);
		glDeleteShader(id);
		throw GlslCompileError(file, error);
	}
}
