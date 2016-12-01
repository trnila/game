#pragma once

#include "Graphics/Texture.h"
#include "Graphics/VBO.h"

class Panel {
public:
	Panel();
	void render();


	Texture *texture;

private:
	VBO vbo;
	Program prog;


};


