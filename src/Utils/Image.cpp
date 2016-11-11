#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#include "Image.h"

Image::Image(const char *file, int comp) {
	data = stbi_load(file, &width, &height, NULL, comp);
	if(!data) {
		throw std::runtime_error(Formatter() << "Could not load texture: " << file);
	}
}

Image::~Image() {
	stbi_image_free(data);
}

uint8_t *Image::getData() const {
	return data;
}

int Image::getWidth() const {
	return width;
}

int Image::getHeight() const {
	return height;
}

uint8_t Image::operator[](int index) {
	return data[index];
}
