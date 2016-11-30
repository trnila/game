#pragma once

#include <assimp/material.h>
#include "VBO.h"
#include "RenderContext.h"

class Material {
public:
	void apply(Program &program) const;
	void createMaterial(const aiMaterial *material, const std::string &path);

	Color ambientColor = Color(1);
	Color diffuseColor = Color(1);
	Color specularColor = Color(1);
	float shininess = 32;
	float shininessStrength = 0.8;
	Texture* texture = nullptr;
	Texture* bumpTexture = nullptr;
};


