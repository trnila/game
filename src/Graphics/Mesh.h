#pragma once

#include <GL/glew.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include "VBO.h"
#include "VAO.h"
#include "RenderContext.h"
#include "Material.h"

class Mesh {
public:
	Mesh(aiMesh &mesh, aiMaterial *material, std::string path);

	void render(RenderContext &context, Program &program);

private:
	VBO vbo;
	VAO vao;
	GLuint ibo;
	int size;
	Material material;
};


