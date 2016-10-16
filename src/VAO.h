#pragma once

#include <GL/glew.h>
#include "BindableResource.h"

class VAOHandler;

class VAO: public BindableResource<VAO, VAOHandler> {
public:
	VAO();
	void enableAttrib(GLuint id);

private:
	unsigned int id;

	void open() {
		glBindVertexArray(id);
	}

	void close() {
		glBindVertexArray(0);
	}

	friend class LockImpl<VAO>;
};

class VAOHandler: public LockImpl<VAO> {
public:
	VAOHandler(VAO &t): LockImpl<VAO>(t) {}

	void enableAttrib(GLuint id) {
		glEnableVertexAttribArray(id);
	}
};