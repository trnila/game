#pragma once

#include "Texture.h"

class CubeMap: public Texture {
public:
	CubeMap(std::vector<std::string> images);

	void setFace(GLuint i, const char *path);

	void setFaces(const std::vector<std::string> &images);
};


