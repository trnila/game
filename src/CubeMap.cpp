#include "CubeMap.h"
#include "stb_image.h"

CubeMap::CubeMap(std::vector<const char *> images): Texture(GL_TEXTURE_CUBE_MAP) {
	int width,height;
	unsigned char* image;
	for(GLuint i = 0; i < images.size(); i++)
	{
		int n;
		image = stbi_load(images[i], &width, &height, &n, 3);
		if(!image) {
			throw std::runtime_error("ff");
		}
		GL_CHECK(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		));
	}

	set(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	set(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	set(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
