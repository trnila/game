#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *file) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int x,y,n;
    unsigned char *data = stbi_load(file, &x, &y, &n, 3);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(data);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);

}
