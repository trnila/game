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

	void render(Camera camera);

private:
	Program program;
	CubeMap* cubemap;
	Model *model;
};


