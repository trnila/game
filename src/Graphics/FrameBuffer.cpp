
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, int depth): width(width), height(height), texture(GL_TEXTURE_2D, width, height, depth, GL_DEPTH_COMPONENT) {
	GL_CHECK(glGenFramebuffers(1, &id));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));

	texture.bind();
	texture.set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	texture.set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	texture.set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture.set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GL_CHECK(glDrawBuffer(GL_NONE));

	texture.attachTo(*this);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Could not create frame buffer");
	}
}

FrameBuffer::~FrameBuffer() {
	GL_CHECK(glDeleteFramebuffers(1, &id));
}
