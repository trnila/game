#include "Texture.h"
#include "../Utils/Formatter.h"
#include "FrameBuffer.h"
#include "../Utils/Image.h"

Texture::Texture(const char *file) {
	create(GL_TEXTURE_2D);

	Image image(file);
	width = image.getWidth();
	height = image.getHeight();
	format = GL_RGB;
	type = GL_UNSIGNED_BYTE;

	setData(image.getData());

	set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GL_CHECK(glGenerateTextureMipmap(id));
}

Texture::Texture(GLuint type, int width, int height, int depth, int component) {
	create(type);
	GL_CHECK(glTexImage2D(type, 0, depth, width, height, 0, component, GL_FLOAT, 0));
}

Texture::Texture(int width, int height) {
	create(GL_TEXTURE_2D);
	this->width = width;
	this->height = height;
	format = GL_RGB;
	type = GL_UNSIGNED_BYTE;

	set(GL_TEXTURE_WRAP_S, GL_REPEAT);
	set(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::bind() {
	GL_CHECK(glBindTexture(target, id));
}

void Texture::create(GLenum target) {
	this->target = target;
	GL_CHECK(glGenTextures(1, &id));
	bind();
}

void Texture::set(int option, int value) {
	GL_CHECK(glTexParameteri(target, option, value));
}

void Texture::attachTo(FrameBuffer &frameBuffer) {
	auto buffer = frameBuffer.activate();
	GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0));
}

Texture::Texture(GLuint type) {
	create(type);
}

Texture::~Texture() {
	GL_CHECK(glDeleteTextures(1, &id));
}

void Texture::setData(const uint8_t *data) {
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, data));
}
