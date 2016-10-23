#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Program.h"
#include "Formatter.h"
#include "utils.h"

Texture::Texture(const char *file) {
	GL_CHECK(glGenTextures(1, &id));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, id));

	int x,y,n;
    unsigned char *data = stbi_load(file, &x, &y, &n, 3);
	if(!data) {
		throw std::runtime_error(Formatter() << "Could not load texture: " << file);
	}

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

	stbi_image_free(data);
}

void Texture::bind(Program &program) {
	program.use();

	GLint location = glGetUniformLocation(program.id, "modelTexture");

	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, id));
	GL_CHECK(glUniform1i(location, 0));
}
