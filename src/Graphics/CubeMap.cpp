#include "CubeMap.h"
#include "../Utils/Formatter.h"
#include "../Utils/Image.h"

CubeMap::CubeMap(std::vector<const char *> images): Texture(GL_TEXTURE_CUBE_MAP) {
	set(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	set(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	set(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	setFaces(images);
}

void CubeMap::setFaces(const std::vector<const char *> &images) {
	for(GLuint i = 0; i < images.size(); i++) {
		setFace(i, images[i]);
	}
}

void CubeMap::setFace(GLuint i, const char *path) {
	Image image(path);
	GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData()));
}
