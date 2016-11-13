#include <GL/glew.h>
#include "Shader.h"
#include "../Utils/utils.h"
#include "../Utils/Formatter.h"
#include <stddef.h>

Shader::Shader(const char *file, GLenum type) {
	id = glCreateShader(type);
	if(!id) {
		throw std::runtime_error("Could not create shader");
	}

	std::string source = preprocessShader(file);



	const GLchar *addr = (GLchar*) source.data();
	GL_CHECK(glShaderSource(id, 1, &addr, NULL));

	GL_CHECK(glCompileShader(id));
	GLint compile_ok = GL_FALSE;
	GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &compile_ok));
	if (compile_ok == GL_FALSE) {
		std::string error = getGLLog(id);
		glDeleteShader(id);
		throw GlslCompileError(file, error, source);
	}
}

std::string Shader::preprocessShader(const char *path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error(Formatter() << "Shader does not exist: " << path);
	}

	std::ostringstream out;

	std::string line;
	while(std::getline(file, line)) {
		std::istringstream is(line);
		std::string word;
		is >> word;

		if(word == "#include") {
			std::string dir = "";

			size_t index = std::string(path).rfind('/');
			if(index >= 0) {
				dir = std::string(path).substr(0, index + 1);
			}

			is >> word;
			word = word.substr(1, word.size() - 2);

			out << preprocessShader((dir + word).c_str());
		} else {
			out << line << "\n";
		}
	}

	return std::string(out.str());
}
