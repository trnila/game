#pragma once

#include "VBO.h"
#include "Program.h"
#include "VAO.h"
#include "RenderContext.h"
#include "Mesh.h"

class Model {
public:
	Model(const char *name, float *vertices, int size);
	~Model();

	Model(const char *path);
	void render(RenderContext &context, Program &program);

private:
	std::vector<Mesh*> meshes;
};
