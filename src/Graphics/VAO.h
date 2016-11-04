#pragma once

#include <GL/glew.h>
#include "BindableResource.h"
#include "../Utils/utils.h"

class VAOHandler;

class VAO: public BindableResource<VAO, VAOHandler> {
public:
	VAO();
	~VAO();
	void enableAttrib(GLuint id);

private:
	unsigned int id;

	void open() {
		GL_CHECK(glBindVertexArray(id));
	}

	void close() {
		GL_CHECK(glBindVertexArray(0));
	}

	friend class LockImpl<VAO>;
};

class VAOHandler: public LockImpl<VAO> {
public:
	VAOHandler(VAO &t): LockImpl<VAO>(t) {}

	void enableAttrib(GLuint id) {
		GL_CHECK(glEnableVertexAttribArray(id));
	}
};