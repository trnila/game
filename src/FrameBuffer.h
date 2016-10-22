#pragma once

#include "BindableResource.h"
#include "FrameBufferHandler.h"
#include "GL/glew.h"

class FrameBuffer: public BindableResource<FrameBuffer, FrameBufferHandler> {
public:
	FrameBuffer();

	void open() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void close() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	GLuint depthTexture;
private:
	GLuint id;


	friend class LockImpl<FrameBuffer>;

};
