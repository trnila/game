#pragma once

#include "VBO.h"
#include "Program.h"

class Model {
public:
	Model(float* vertices, float *colors, int size);
	void render();

private:
	VBO vbo, colorsVbo;
	VAO vao;
	int size;
};