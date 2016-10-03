#pragma once

#include "VBO.h"
#include "Program.h"
#include "VAO.h"
#include "RenderContext.h"

class Model {
public:
	Model(float* vertices, float *colors, int size);

	Model(const char *path);
	void render(RenderContext &context);

private:
	VBO vbo, colorsVbo;
	VAO vao;
	int size;
};
