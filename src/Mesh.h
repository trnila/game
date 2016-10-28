#pragma once

#include <GL/glew.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include "VBO.h"
#include "VAO.h"
#include "RenderContext.h"

class Mesh {
public:
	Mesh(aiMesh &mesh, aiMaterial *material);

	void render(RenderContext &context, Program &program);

private:
	VBO vbo, colorsVbo;
	VAO vao;
	GLuint ibo = 0;
	int size;
	Color ambientColor;
	Color diffuseColor;
	glm::vec3 specularColor;
	float shininess = 32;
	float shininessStrength = 0.8;
};


