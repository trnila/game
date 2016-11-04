#pragma once

#include "Program.h"
#include "Texture.h"
#include "CubeMap.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"

class Skybox {
public:
	Skybox();
	~Skybox();

	void render(RenderContext &c);

	Program program;
private:
	CubeMap* cubemap;
	Model *model;
};


