#pragma once

#include <GL/glew.h>
#include <assimp/mesh.h>
#include "VBO.h"
#include "VAO.h"
#include "RenderContext.h"

class Mesh {
public:
	Mesh(aiMesh& mesh);

	void render(RenderContext &context);

private:
	VBO vbo, colorsVbo;
	VAO vao;
	GLuint ibo = 0;
	int size;
};


