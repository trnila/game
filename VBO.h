#pragma once

#include <GL/glew.h>

class VBO {
public:
	VBO() {
		glGenBuffers(1, &id);
	}

	void bind() {

		glBindBuffer(GL_ARRAY_BUFFER, id);

		
	}

	void setData(const char *data, size_t size) {
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
private:
	GLuint id;
};

class VAO {
public:
	VAO() {
		glGenVertexArrays(1, &id);
	}

	void bind() {
		glBindVertexArray(id);
	}

	void enableAttrib(int id) {
		glEnableVertexAttribArray(0);
	}



private:
	GLuint id;
};

