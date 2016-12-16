#pragma once

#include "Texture.h"
#include "VBO.h"
#include "Program.h"

class Panel {
public:
	Panel();
	void render();

private:
	VBO vbo;
	Program prog;
	Texture *texture;
};


