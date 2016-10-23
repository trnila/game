
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, int depth): width(width), height(height) {
	GL_CHECK(glGenFramebuffers(1, &id));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, id));

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GL_CHECK(glGenTextures(1, &depthTexture));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthTexture));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, depth, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0));

	GL_CHECK(glDrawBuffer(GL_NONE)); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {printf("err\n");}
}