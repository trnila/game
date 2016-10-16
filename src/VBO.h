#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "Type.h"
#include "BindableResource.h"
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
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void close() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	friend class LockImpl<VBO>;
};


class VBOHandler: public LockImpl<VBO> {
public:
	template<typename T>
	void setData(const T *data, size_t size, size_t blockSize) {
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T) * blockSize, data, GL_STATIC_DRAW);
	}

	template<typename T>
	void setPointer(GLuint layoutPos, int offset) {
		glVertexAttribPointer(layoutPos, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offset);
	}

private:
	VBOHandler(VBO &t) : LockImpl(t) {}

	friend class BindableResource<VBO, VBOHandler>;
};
