#pragma once

#include "BindableResource.h"
#include "FrameBufferHandler.h"
#include "GL/glew.h"

class FrameBuffer: public BindableResource<FrameBuffer, FrameBufferHandler> {
public:
	FrameBuffer(int width, int height, int depth);

	void open() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glViewport(0, 0, width, height);
	}

	void close() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	GLuint depthTexture;
private:
	GLuint id;
	int width, height;


	friend class LockImpl<FrameBuffer>;

};
