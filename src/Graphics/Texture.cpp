#include "Texture.h"
#include "../Utils/Formatter.h"
#include "FrameBuffer.h"
#include "../Utils/Image.h"

Texture::Texture(const char *file): type(GL_TEXTURE_2D) {
	GL_CHECK(glGenTextures(1, &id));
	bind();

	Image image(file);

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData()));

	set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::bind() {
	GL_CHECK(glBindTexture(type, id));
}

void Texture::create() {
	GL_CHECK(glGenTextures(1, &id));
	bind();
}

Texture::Texture(GLuint type, int width, int height, int depth, int component): type(type) {
	create();
	GL_CHECK(glTexImage2D(type, 0, depth, width, height, 0, component, GL_FLOAT, 0));
}

void Texture::set(int option, int value) {
	GL_CHECK(glTexParameteri(type, option, value));
}

void Texture::attachTo(FrameBuffer &frameBuffer) {
	auto buffer = frameBuffer.activate();
	GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0));
}

Texture::Texture(GLuint type): type(type) {
	create();
}

Texture::~Texture() {
	GL_CHECK(glDeleteTextures(1, &id));
}
