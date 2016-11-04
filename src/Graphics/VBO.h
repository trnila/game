#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "../Type.h"
#include "BindableResource.h"
#include "../Utils/utils.h"
#include <typeinfo>
#include <stdexcept>

class VBOHandler;

class VBO: public BindableResource<VBO, VBOHandler> {
public:
	VBO();
	~VBO();

private:
	GLuint id;

	void open() {
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, id));
	}

	void close() {
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	friend class LockImpl<VBO>;
};


class VBOHandler: public LockImpl<VBO> {
public:
	template<typename T>
	void setData(const T *data, size_t size, size_t blockSize) {
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size * sizeof(T) * blockSize, data, GL_STATIC_DRAW));
	}

	template<typename T>
	void setPointer(GLuint layoutPos, int offset) {
		GL_CHECK(glVertexAttribPointer(layoutPos, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offset));
	}

private:
	VBOHandler(VBO &t) : LockImpl(t) {}

	friend class BindableResource<VBO, VBOHandler>;
};
