#pragma once

#include <stdexcept>
#include <GL/glew.h>
#include <sstream>

class GlslCompileError: public std::exception {
public:
	GlslCompileError(const char *source, std::string info, std::string code) {
		this->source = source;
		this->info = info;

		std::ostringstream os;
		os << "Shader compilation error: " << info << " in " << source << "\n";

		int w, lineNum;
		sscanf(info.c_str(), "%d(%d)", &w, &lineNum);
		std::string line = extractLine(code, lineNum);
		if(!line.empty()) {
			os << line;
		}

		description = os.str();
	}

	std::string extractLine(const std::string &code, int lineNum) const {
		int line = 1;
		std::string str;
		for(int pos = 0; pos < code.length(); pos++) {
			if(code[pos] == '\n') {
				line++;
				if(line == lineNum) {
					pos++;
					int end = code.find('\n', pos);
					str = code.substr(pos, end - pos);
					break;
				}
			}
		}
		return str;
	}

	virtual const char* what() const throw () {
		return description.c_str();
	}

private:
	const char* source;
	std::string info;
	std::string line;

	std::string description;
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



