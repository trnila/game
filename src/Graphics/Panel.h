#pragma once

#include "Texture.h"
#include "VBO.h"
#include "Program.h"

class Panel {
public:
	Panel();
	void render();


	Texture *texture;

private:
	VBO vbo;
	Program prog;
};


