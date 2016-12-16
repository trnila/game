#pragma once

#include "Graphics/Texture.h"
#include "Graphics/VBO.h"
#include "Graphics/Program.h"

class Panel {
public:
	Panel();
	void render();


	Texture *texture;

private:
	VBO vbo;
	Program prog;
};


