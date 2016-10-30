#pragma once

#include "Texture.h"

class CubeMap: public Texture {
public:
	CubeMap(std::vector<const char *> images);
};


