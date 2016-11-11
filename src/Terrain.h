
#pragma once


#include "Graphics/Program.h"
#include "Graphics/VBO.h"
#include "Graphics/VAO.h"

class Terrain {
public:
	Terrain();
	void draw(Camera &cam);

private:
	Program prog;
	/*VBO vbo;
	VAO vao;*/
};


