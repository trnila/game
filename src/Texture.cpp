#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Program.h"
#include "Formatter.h"

Texture::Texture(const char *file) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int x,y,n;
    unsigned char *data = stbi_load(file, &x, &y, &n, 3);
	if(!data) {
		throw std::runtime_error(Formatter() << "Could not load texture: " << file);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(data);
}

void Texture::bind(Program &program) {
	program.use();

	GLint location = glGetUniformLocation(program.id, "modelTexture");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glUniform1i(location, 0);
}
