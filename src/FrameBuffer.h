#pragma once

#include "BindableResource.h"
#include "FrameBufferHandler.h"
#include "GL/glew.h"
#include "utils.h"
#include "Texture.h"

class FrameBuffer: public BindableResource<FrameBuffer, FrameBufferHandler> {
public:
	FrameBuffer(int width, int height, int depth);

	void open() {
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));
		GL_CHECK(glViewport(0, 0, width, height));
	}

	void close() {
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	Texture& getTexture() {
		return texture;
	}


	GLuint depthTexture;
private:
	GLuint id;
	int width, height;
	Texture texture;


	friend class LockImpl<FrameBuffer>;

};
