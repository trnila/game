#pragma once

#include "BindableResource.h"
#include "FrameBufferHandler.h"
#include "GL/glew.h"
#include "../Utils/utils.h"
#include "Texture.h"

class FrameBuffer: public BindableResource<FrameBuffer, FrameBufferHandler> {
public:
	FrameBuffer(int width, int height, int depth);
	~FrameBuffer();

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

private:
	GLuint id;
	int width, height;
	Texture texture;
	GLuint depthTexture;

	friend class FrameBufferHandler;
};
