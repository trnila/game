#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Formatter.h"
#include "FrameBuffer.h"

Texture::Texture(const char *file): type(GL_TEXTURE_2D) {
	GL_CHECK(glGenTextures(1, &id));
	bind();

	int x,y,n;
    unsigned char *data = stbi_load(file, &x, &y, &n, 3);
	if(!data) {
		throw std::runtime_error(Formatter() << "Could not load texture: " << file);
	}

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

	set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(data);
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
